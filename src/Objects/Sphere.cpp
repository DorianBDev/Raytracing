#include "Sphere.h"

#include "Utils/Utils.h"

#include <utility>

Sphere::Sphere(Material material, const Color& color, Vector3 coordinates, double radius)
    : Object(material, color),
      m_coordinates(std::move(coordinates)),
      m_radius(radius)
{
}

std::optional<Vector3> Sphere::getIntersection(const Ray& ray) const
{
    const Vector3& origin = ray.getOrigin();
    const Vector3& direction = ray.getDirection();

    double a = pow2(direction.x()) + pow2(direction.y()) + pow2(direction.z());

    double b =
            2 * ((origin.x() - m_coordinates.x()) * direction.x() + (origin.y() - m_coordinates.y()) * direction.y() +
                 (origin.z() - m_coordinates.z()) * direction.z());

    double c = pow2(origin.x() - m_coordinates.x()) + pow2(origin.y() - m_coordinates.y()) +
               pow2(origin.z() - m_coordinates.z()) - pow2(m_radius);

    double discriminant = pow2(b) - 4 * a * c;

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

std::optional<Ray> Sphere::getSecondaryRay(const Vector3& intersectionPoint, const Vector3& originLight) const
{
    return Ray(intersectionPoint, originLight - intersectionPoint, SECONDARY);
}

std::optional<Vector3> Sphere::getRefractedIntersection(const Ray& ray) const
{
    const Vector3& origin = ray.getOrigin();
    const Vector3& direction = ray.getDirection();

    double a = pow2(direction.x()) + pow2(direction.y()) + pow2(direction.z());

    double b =
            2 * ((origin.x() - m_coordinates.x()) * direction.x() + (origin.y() - m_coordinates.y()) * direction.y() +
                 (origin.z() - m_coordinates.z()) * direction.z());

    double c = pow2(origin.x() - m_coordinates.x()) + pow2(origin.y() - m_coordinates.y()) +
               pow2(origin.z() - m_coordinates.z()) - pow2(m_radius);

    double discriminant = pow2(b) - 4 * a * c;

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
            return direction * t2 + origin;

        if (t2 > 0)
            return direction * t1 + origin;
    }

    return std::nullopt;
}

Vector3 Sphere::getNormal(const Vector3& intersectionPoint) const
{
    return intersectionPoint - m_coordinates;
}
