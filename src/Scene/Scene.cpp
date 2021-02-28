#include "Scene.h"

#include "Config.h"
#include "Light/Directional.h"
#include "Light/Punctual.h"
#include "Light/Spot.h"
#include "Objects/Model.h"
#include "Objects/Plane.h"
#include "Objects/Sphere.h"
#include "Utils/Math.h"
#include "Utils/Utils.h"

#include <SFML/Graphics.hpp>
#include <cmath>

#ifdef PARALLELIZATION
#include <algorithm>
#include <execution>
#endif

#include <cmath>
#include <map>
#include <numeric>
#include <utility>

Scene::Scene(std::shared_ptr<Camera> camera, double ambientLight)
    : m_camera(std::move(camera)),
      m_ambientLight(ambientLight)
{
}

void Scene::loadScene(const std::string& path)
{
    std::ifstream file(path);

    std::stringstream stream;
    std::string line;
    std::string word;

    std::string pathModel;
    double intensity = 0.0;
    double radius = 0.0;
    double scale = 0.0;

    Material material(0, 0, 0, 0);
    Color color(0, 0, 0);
    Vector3 coordinates;
    Vector3 secondCoordinates;
    Vector3 direction;
    Vector3 normal;
    Vector3 angle;

    if (!file.is_open())
        throw std::runtime_error("Error when opening the config file.");

    while (getline(file, line))
    {
        stream = std::stringstream(line);
        getline(stream, word, ' ');

        if (word == "Punctual")
        {
            getline(stream, word, ' ');
            intensity = std::stod(word);
            color = splitColor(stream);
            coordinates = splitVector3(stream);

            addLight<Punctual>(intensity, color, coordinates);
        }
        else if (word == "Directional")
        {
            getline(stream, word, ' ');
            intensity = std::stod(word);
            color = splitColor(stream);
            coordinates = splitVector3(stream);
            secondCoordinates = splitVector3(stream);
            direction = splitVector3(stream);

            addLight<Directional>(intensity, color, coordinates, secondCoordinates, direction);
        }
        else if (word == "Spot")
        {
            getline(stream, word, ' ');
            intensity = std::stod(word);
            color = splitColor(stream);
            coordinates = splitVector3(stream);
            direction = splitVector3(stream);
            getline(stream, word, ' ');

            addLight<Spot>(intensity, color, coordinates, direction, std::stod(word));
        }
        else if (word == "Sphere")
        {
            material = splitMaterial(stream);
            color = splitColor(stream);
            coordinates = splitVector3(stream);

            getline(stream, word, ' ');
            radius = std::stod(word);

            addObject<Sphere>(material, color, coordinates, radius);
        }
        else if (word == "Plane")
        {
            material = splitMaterial(stream);
            color = splitColor(stream);
            coordinates = splitVector3(stream);
            normal = splitVector3(stream);

            addObject<Plane>(material, color, coordinates, normal);
        }
        else if (word == "Model")
        {
            std::cout << line << std::endl;

            material = splitMaterial(stream);
            color = splitColor(stream);
            getline(stream, pathModel, ' ');
            coordinates = splitVector3(stream);
            angle = splitVector3(stream);
            getline(stream, word, ' ');
            scale = std::stod(word);

            addObject<Model>(material, color, pathModel, coordinates, angle, scale);
        }
    }
}

Material Scene::splitMaterial(std::stringstream& stream)
{
    std::string word;
    getline(stream, word, ' ');

    double reflectivity = 0.0;
    double refractivity = 0.0;
    double transparency = 0.0;

    if (word == "metal")
    {
        getline(stream, word, ' ');
        reflectivity = std::stod(word);

        return Materials::metal(reflectivity);
    }

    if (word == "transparent")
    {
        getline(stream, word, ' ');
        reflectivity = std::stod(word);

        getline(stream, word, ' ');
        refractivity = std::stod(word);

        getline(stream, word, ' ');
        transparency = std::stod(word);

        return Materials::transparent(reflectivity, refractivity, transparency);
    }

    throw std::runtime_error("Error when opening the config file. (splitMaterial");
}

Vector3 Scene::splitVector3(std::stringstream& stream)
{
    std::string word;

    double x = 0.0;
    double y = 0.0;
    double z = 0.0;

    getline(stream, word, ' ');
    x = std::stod(word);

    getline(stream, word, ' ');
    y = std::stod(word);

    getline(stream, word, ' ');
    z = std::stod(word);

    return Vector3(x, y, z);
}

Color Scene::splitColor(std::stringstream& stream)
{
    std::string word;

    uint8_t x = 0;
    uint8_t y = 0;
    uint8_t z = 0;

    getline(stream, word, ' ');

    if (word == "defined")
    {
        getline(stream, word, ' ');
        return getColor(word);
    }

    getline(stream, word, ' ');
    x = static_cast<uint8_t>(std::stoi(word));

    getline(stream, word, ' ');
    y = static_cast<uint8_t>(std::stoi(word));

    getline(stream, word, ' ');
    z = static_cast<uint8_t>(std::stoi(word));

    return Color(x, y, z);
}

Color Scene::getColor(const std::string& name)
{
    if (name == "red")
        return Colors::red();
    if (name == "blue")
        return Colors::blue();
    if (name == "green")
        return Colors::green();
    if (name == "black")
        return Colors::black();
    if (name == "white")
        return Colors::white();

    return Colors::white();
}

Scene& Scene::generate(const std::string& imagePath, unsigned int recursivity)
{
    compute(recursivity)->saveToFile(imagePath);
    m_lastSavedImage = imagePath;

    return *this;
}

Scene& Scene::show()
{
    auto width = static_cast<unsigned int>(m_camera->getResolution().width());
    auto height = static_cast<unsigned int>(m_camera->getResolution().height());

    sf::RenderWindow window(sf::VideoMode(width, height), "Raytracing");

    sf::Image image;
    if (!m_lastSavedImage.empty())
    {
        image.loadFromFile(m_lastSavedImage);
    }
    else
    {
        image = *compute();
    }

    sf::Texture texture;
    texture.loadFromImage(image);

    sf::Sprite sprite;
    sprite.setTexture(texture);

    while (window.isOpen())
    {
        sf::Event event{};
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(sprite);
        window.display();
    }

    return *this;
}

void Scene::enableAntialiasing(std::size_t antialiasingSampling)
{
    m_antialiasingSampling = antialiasingSampling;
}

void Scene::disableAntialiasing()
{
    m_antialiasingSampling = 0;
}

std::shared_ptr<sf::Image> Scene::compute(unsigned int recursivity) const
{
    auto resolution = m_camera->getResolution();

    // Create the image
    auto res = std::make_shared<sf::Image>();
    res->create(static_cast<unsigned int>(resolution.width()), static_cast<unsigned int>(resolution.height()));

    // Projection plan size
    const double projectionPlanSizeX = 2.0;
    const double projectionPlanSizeY = projectionPlanSizeX * (1.0 / m_camera->getRatio());

    // Center
    Vector3 projectionPlanCenter;
    projectionPlanCenter = Vector3(0.0, 0.0, m_camera->getFocal());

    // Max
    Vector3 imagePlanMax;
    imagePlanMax.setX(projectionPlanCenter.x() + projectionPlanSizeX / 2.0);
    imagePlanMax.setY(projectionPlanCenter.y() + projectionPlanSizeY / 2.0);
    imagePlanMax.setZ(projectionPlanCenter.z());

    // Min
    Vector3 imagePlanMin;
    imagePlanMin.setX(projectionPlanCenter.x() - projectionPlanSizeX / 2.0);
    imagePlanMin.setY(projectionPlanCenter.y() - projectionPlanSizeY / 2.0);
    imagePlanMin.setZ(projectionPlanCenter.z());

    // Step
    double stepX = projectionPlanSizeX / static_cast<double>(resolution.width());
    double stepY = projectionPlanSizeY / static_cast<double>(resolution.height());

    // Create the image, pixel by pixel
#ifdef PARALLELIZATION

    // Prepare parallelization
    std::vector<std::size_t> count(resolution.width());
    std::iota(std::begin(count), std::end(count), 0);

    std::for_each(std::execution::par, std::begin(count), std::end(count), [&](std::size_t x) {
#else
    for (std::size_t x = 0; x < resolution.width(); x++)
    {
#endif
        for (std::size_t y = 0; y < resolution.height(); y++)
        {
            Color color = m_backgroundColor;

            if (m_antialiasingSampling != 0)
            {
                int padding = static_cast<int>(std::sqrt(m_antialiasingSampling));

                double samplingStepX = stepX / padding;
                double samplingStepY = stepY / padding;

                int centeredPadding = padding / 2;

                Vector3 colors;

                double baseX = x * stepX + imagePlanMin.x() - stepX / (padding * 2);
                double baseY = y * stepY + imagePlanMin.y() - stepY / (padding * 2);

                // Sampling
                for (int i = 0; i <= centeredPadding; i++)
                {
                    for (int j = 0; j <= centeredPadding; j++)
                    {
                        // Coordinates
                        double projectionPlanPointX = baseX + i * samplingStepX;
                        double projectionPlanPointY = baseY + j * samplingStepY;

                        // Direction
                        Vector3 direction =
                                Vector3(projectionPlanPointX, projectionPlanPointY, projectionPlanCenter.z());

                        // Create the ray
                        Ray ray(m_camera->getCoordinates(),
                                Matrix::normalize(m_camera->getDirection() + direction).toVector3(),
                                PRIMARY);

                        // Get the intersection object and point
                        auto intersection = getIntersectedObject(ray);
                        if (intersection.has_value())
                        {
                            auto& [object, point] = intersection.value();

                            colors = colors + getColor(object, point, ray, recursivity);
                        }
                        else
                            colors = colors + m_backgroundColor;
                    }
                }

                color = colors * (1.0 / static_cast<double>(m_antialiasingSampling));
            }
            else
            {
                // Coordinates
                double projectionPlanPointX = x * stepX + imagePlanMin.x();
                double projectionPlanPointY = y * stepY + imagePlanMin.y();

                // Direction
                Vector3 direction = Vector3(projectionPlanPointX, projectionPlanPointY, projectionPlanCenter.z());

                // Create the ray
                Ray ray(m_camera->getCoordinates(),
                        Matrix::normalize(m_camera->getDirection() + direction).toVector3(),
                        PRIMARY);

                // Get the intersection object and point
                auto intersection = getIntersectedObject(ray);
                if (intersection.has_value())
                {
                    auto& [object, point] = intersection.value();

                    color = getColor(object, point, ray, recursivity);
                }
            }

            // Compute the pixel color
            res->setPixel(static_cast<unsigned int>(x), static_cast<unsigned int>(y), color.toSFMLColor());
        }

#ifdef PARALLELIZATION
    });
#else
    }
#endif

    return res;
}

IntersectionResult Scene::getIntersectedObject(const Ray& ray) const
{
    std::map<std::shared_ptr<Object>, Vector3> intersections;

    // Get all objects that intersect with the ray
    for (const auto& object : m_objects)
    {
        auto intersection = object->getIntersection(ray);

        if (intersection.has_value())
        {
            intersections[object] = intersection.value();
        }
    }

    // Check if no intersection
    if (intersections.empty())
        return std::nullopt;

    // Get closer object
    std::shared_ptr<Object> closerObject = nullptr;
    Vector3& closerIntersectionPoint = intersections.begin()->second;
    double minDistance = -1;
    for (auto& [object, intersection] : intersections)
    {
        double distance = intersection.distance(ray.getOrigin());

        if (Matrix::areApproximatelyEqual(intersection, ray.getOrigin(), 0.0000001))
            continue;

        if (distance < minDistance || minDistance == -1)
        {
            closerObject = object;
            closerIntersectionPoint = intersection;
            minDistance = distance;
        }
    }

    if (closerObject == nullptr)
        return std::nullopt;

    return {{closerObject, closerIntersectionPoint}};
}

double lightAttenuation(double distance)
{
    static const double b = 3.0;
    static const double c = 3.0;

    return 1.0 / (b * distance + c * pow2(distance));
}

std::pair<double, Color> Scene::computeLight(const std::shared_ptr<Object>& intersectionObject,
                                             const Vector3& intersectionPoint,
                                             const Ray& primaryRay) const
{
    /* Light global illumination */
    double i = 0;

    /* Light colors */
    Color color;

    for (const auto& light : m_lights)
    {
        if (!light->isEnLight(intersectionPoint))
            continue;

        auto origin = light->getOrigin(intersectionPoint);

        if (!origin.has_value())
            continue;

        auto ray = intersectionObject->getSecondaryRay(intersectionPoint, origin.value());

        if (!ray.has_value())
            continue;

        if (!isIlluminated(ray.value(), origin.value()))
            continue;

        // fatt origin->distance(ray->getOrigin())
        double attenuation = lightAttenuation(origin->distance(ray->getOrigin()) * (1.0 / light->getIntensity()));

        // N
        Vector3 n = intersectionObject->getNormal(intersectionPoint);

        // H
        Vector3 h = ray->getDirection() + primaryRay.getDirection();
        h.normalize();

        // L
        Vector3 l = ray->getDirection();

        // Alpha/n
        const double shininess = intersectionObject->getMaterial().shininess();

        /* Specular */
        double is = std::max<double>(std::pow(Matrix::dot(n, h), shininess), 0.) * attenuation;

        /* Diffuse */
        double id = Matrix::dot(n, l) * attenuation;

        i += is + id;
        color += light->getColor() * light->getIntensity() * attenuation;
    }

    return {i, color};
}

bool Scene::isIlluminated(const Ray& secondaryRay, const Vector3& lightOrigin) const
{
    std::map<std::shared_ptr<Object>, Vector3> intersections;

    // Change the origin of the secondary to the light origin, the direction stay the same
    // It will allow to handle the case we need to gow throw a sphere (other extremity of a sphere)
    Ray ray(lightOrigin, secondaryRay.getDirection() * -1, secondaryRay.getType());

    // The intersection point
    const auto& intersectionPoint = secondaryRay.getOrigin();

    // Get all objects that intersect with the ray
    for (const auto& object : m_objects)
    {
        auto intersection = object->getIntersection(ray);
        if (intersection.has_value())
        {
            intersections[object] = intersection.value();
        }
    }

    // Check if no intersection
    if (intersections.empty())
        return true;

    // Distance to the light (from the intersection point)
    double lightDistance = lightOrigin.distance(intersectionPoint);

    // Get closer object
    for (auto& element : intersections) // NOLINT
    {
        auto& intersection = element.second;

        // Distance to the light (from the newly found intersection point)
        double distance = lightOrigin.distance(intersection);

        if (areDoubleApproximatelyEqual(distance, lightDistance, 0.0000001))
            continue;

        if (distance < lightDistance)
            return false;
    }

    return true;
}

std::optional<Color> Scene::computeReflection(const std::shared_ptr<Object>& intersectionObject,
                                              const Vector3& intersectionPoint,
                                              const Ray& primaryRay,
                                              unsigned int recursivity) const
{
    if (intersectionObject->getMaterial().isOpaque())
        return std::nullopt;

    // Get reflected direction
    auto reflectedDirection = Matrix::reflection(primaryRay.getDirection(),                         // Primary direction
                                                 intersectionObject->getNormal(intersectionPoint)); // Normal

    // Create the reflected ray
    Ray reflectedRay(intersectionPoint, reflectedDirection, PRIMARY);

    // Result of the reflection
    auto reflectionResult = getIntersectedObject(reflectedRay);
    if (!reflectionResult.has_value())
        return std::nullopt;

    auto reflectedObject = reflectionResult.value().first;
    auto reflectedIntersection = reflectionResult.value().second;

    if (recursivity != 0)
        return getColor(reflectedObject, reflectedIntersection, reflectedRay, recursivity - 1);

    return reflectedObject->getColor();
}

std::optional<Color> Scene::computeRefraction(const std::shared_ptr<Object>& intersectionObject,
                                              const Vector3& intersectionPoint,
                                              const Ray& primaryRay,
                                              unsigned int recursivity) const
{
    if (!intersectionObject->getMaterial().isTransparent())
        return std::nullopt;

    // Get refracted direction
    auto refractedDirection = Matrix::refraction(primaryRay.getDirection(),                        // Primary direction
                                                 intersectionObject->getNormal(intersectionPoint), // Normal
                                                 1.0,
                                                 intersectionObject->getMaterial().refractivity()); // Refractivity

    // Create the reflected ray
    Ray refractedRay(intersectionPoint, refractedDirection, PRIMARY);

    // Result of the reflection
    auto reflectionResult = getIntersectedObject(refractedRay);
    if (!reflectionResult.has_value())
        return std::nullopt;

    auto reflectedObject = reflectionResult.value().first;
    auto reflectedIntersection = reflectionResult.value().second;

    if (reflectedObject == intersectionObject)
    {
        refractedDirection = Matrix::refraction(refractedRay.getDirection(),
                                                reflectedObject->getNormal(reflectedIntersection) * -1,
                                                reflectedObject->getMaterial().refractivity(),
                                                1.0);

        // Create the reflected ray
        refractedRay = Ray(reflectedIntersection, refractedDirection, PRIMARY);

        // Result of the reflection
        reflectionResult = getIntersectedObject(refractedRay);
        if (!reflectionResult.has_value())
            return std::nullopt;

        reflectedObject = reflectionResult.value().first;
        reflectedIntersection = reflectionResult.value().second;
    }

    if (recursivity != 0)
        return getColor(reflectedObject, reflectedIntersection, refractedRay, recursivity - 1);

    return reflectedObject->getColor();
}

Color Scene::getColor(const std::shared_ptr<Object>& intersectionObject,
                      const Vector3& intersectionPoint,
                      const Ray& primaryRay,
                      unsigned int recursivity) const
{
    double r = intersectionObject->getMaterial().reflectivity();
    double t = intersectionObject->getMaterial().transparency();

    auto light = computeLight(intersectionObject, intersectionPoint, primaryRay);
    auto reflection = computeReflection(intersectionObject, intersectionPoint, primaryRay, recursivity);
    auto refraction = computeRefraction(intersectionObject, intersectionPoint, primaryRay, recursivity);

    Color color = intersectionObject->getColor() * m_ambientLight +
                  intersectionObject->getColor() * (1 - m_ambientLight) * light.first + light.second * light.first;

    // Set the color
    if (reflection.has_value())
        color = color * (1 - r) + reflection.value() * r;

    // Refraction
    if (refraction.has_value())
        color = color * (1 - t) + refraction.value() * t;
    else
        color = color * (1 - t) + m_backgroundColor * t;

    return color;
}
