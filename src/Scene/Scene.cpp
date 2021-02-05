#include "Scene.h"

#include "Utils/Utils.h"

#include <map>
#include <utility>

Scene::Scene(std::shared_ptr<Camera> camera) : m_camera(std::move(camera))
{
}

Scene& Scene::addLight(const std::shared_ptr<Light>& light)
{
    m_lights.push_back(light);

    return *this;
}

Scene& Scene::addObject(const std::shared_ptr<Object>& object)
{
    m_objects.push_back(object);

    return *this;
}

Scene& Scene::generate(const std::string& imagePath)
{
    compute()->saveToFile(imagePath);

    return *this;
}

std::shared_ptr<sf::Image> Scene::compute()
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
    for (std::size_t x = 0; x < resolution.width(); x++)
    {
        for (std::size_t y = 0; y < resolution.height(); y++)
        {
            // Coordinates
            double projectionPlanPointX = x * stepX + imagePlanMin.x();
            double projectionPlanPointY = y * stepY + imagePlanMin.y();

            // Direction
            Vector3 direction;
            direction = Vector3(projectionPlanPointX, projectionPlanPointY, projectionPlanCenter.y());

            // Create the ray
            Ray ray(m_camera->getCoordinates(),
                    Matrix::normalize(m_camera->getDirection() + direction).toVector3(),
                    PRIMARY);

            // Compute the pixel color
            res->setPixel(static_cast<unsigned int>(x), static_cast<unsigned int>(y), getPixelColor(ray));
        }
    }

    return res;
}

sf::Color Scene::getPixelColor(const Ray& ray)
{
    std::map<std::shared_ptr<Object>, Vector3> intersections;

    // Get all objects that intersect with the ray
    for (auto& object : m_objects)
    {
        auto intersection = object->getIntersection(ray);
        if (intersection.has_value())
        {
            intersections[object] = intersection.value();
        }
    }

    // Check if no intersection
    if (intersections.empty())
        return sf::Color();

    // Get closer object
    std::shared_ptr<Object> closerObject = intersections.begin()->first;
    Vector3 closerNorm = intersections.begin()->second;
    for (auto& [object, intersection] : intersections)
    {
        if (intersection.getNorm() < closerNorm.getNorm())
        {
            closerObject = object;
            closerNorm = intersection;
        }
    }

    // Return the color of the nearest object
    auto color = closerObject->getColor();
    return sf::Color(color.red(), color.green(), color.blue(), color.alpha());
}