#include "Scene.h"

#include "Config.h"
#include "Utils/Math.h"
#include "Utils/Utils.h"

#include <SFML/Graphics.hpp>

#ifdef PARALLELIZATION
#include <algorithm>
#include <execution>
#endif

#include <cmath>
#include <map>
#include <numeric>
#include <utility>

Scene::Scene(std::shared_ptr<Camera> camera) : m_camera(std::move(camera))
{
}

Scene& Scene::generate(const std::string& imagePath)
{
    compute()->saveToFile(imagePath);
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

std::shared_ptr<sf::Image> Scene::compute() const
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
            // Coordinates
            double projectionPlanPointX = x * stepX + imagePlanMin.x();
            double projectionPlanPointY = y * stepY + imagePlanMin.y();

            // Direction
            Vector3 direction = Vector3(projectionPlanPointX, projectionPlanPointY, projectionPlanCenter.y());

            // Create the ray
            Ray ray(m_camera->getCoordinates(),
                    Matrix::normalize(m_camera->getDirection() + direction).toVector3(),
                    PRIMARY);

            Color color = m_backgroundColor;

            // Get the intersection object and point
            auto intersection = getIntersectedObject(ray);
            if (intersection.has_value())
            {
                auto& [object, point] = intersection.value();

                color = getColor(object, point, ray, 0);
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

Color Scene::computeLight(const std::shared_ptr<Object>& intersectionObject,
                          const Vector3& intersectionPoint,
                          const Ray& primaryRay) const
{
    Color res(0, 0, 0, 0);

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

        double attenuation = 1 / origin->distance(ray->getOrigin());

        Vector3 n = intersectionObject->getNormal(intersectionPoint);

        Vector3 h = ray->getDirection() + primaryRay.getDirection();
        h.normalize();

        const double shininess = 2.0;

        double intensity = attenuation * light->getIntensity() * std::pow(Matrix::dot(n, h), shininess);
        res += light->getColor() * intensity;
    }

    //res.print();

    return res;
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
        std::cout << "lol" << std::endl;

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
    Color color;

    double r = intersectionObject->getMaterial().reflectivity();
    double t = intersectionObject->getMaterial().transparency();

    auto light = computeLight(intersectionObject, intersectionPoint, primaryRay);
    auto reflection = computeReflection(intersectionObject, intersectionPoint, primaryRay, recursivity);
    auto refraction = computeRefraction(intersectionObject, intersectionPoint, primaryRay, recursivity);

    // Set the color
    if (reflection.has_value())
        color = intersectionObject->getColor() * (1 - r) + reflection.value() * r;
    else
        color = intersectionObject->getColor();

    color += light;

    // Refraction
    if (refraction.has_value())
        color = color * (1 - t) + refraction.value() * t;
    else
        color = color * (1 - t) + m_backgroundColor * t;

    return color;
}