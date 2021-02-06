#include "Sphere.h"

#include <utility>

Sphere::Sphere(Color color, Vector3 coordinates, double radius)
    : Object(color),
      m_coordinates(std::move(coordinates)),
      m_radius(radius)
{
}

std::optional<Vector3> Sphere::getIntersection(Ray ray)
{
    if (ray.getType() != PRIMARY)
        return std::nullopt;

    Vector3 origin = ray.getOrigin();
    Vector3 direction = ray.getDirection();

    double a = std::pow(direction.x(), 2) + std::pow(direction.y(), 2) + std::pow(direction.z(), 2);

    double b =
            2 * ((origin.x() - m_coordinates.x()) * direction.x() + (origin.y() - m_coordinates.y()) * direction.y() +
                 (origin.z() - m_coordinates.z()) * direction.z());

    double c = std::pow(origin.x() - m_coordinates.x(), 2) + std::pow(origin.y() - m_coordinates.y(), 2) +
               std::pow(origin.z() - m_coordinates.z(), 2) - std::pow(m_radius, 2);

    double discriminant = std::pow(b, 2) - 4 * a * c;

    if (discriminant == 0)
    {
        // One solution exist, it is a tangent point
        double t = -b / (2 * a);

        return direction * t + origin;
    }

    if (discriminant > 0)
    {
        double t1 = (-b - std::sqrt(discriminant)) / (2 * a);
        double t2 = (-b + std::sqrt(discriminant)) / (2 * a);

        if (t1 > 0)
            return direction * t1 + origin;

        if (t2 > 0)
            return direction * t2 + origin;
    }

    return std::nullopt;
}

std::optional<Ray> Sphere::getSecondaryRay(Vector3 intersectionPoint, Vector3 originLight)
{
    return Ray(intersectionPoint, originLight - intersectionPoint, SECONDARY);
}
