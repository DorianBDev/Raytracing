#include "Plane.h"

#include <utility>

Plane::Plane(Material material, const Color& color, Vector3 coordinates, double d)
    : Object(material, color),
      m_coordinates(std::move(coordinates)),
      m_d(d)
{
}

std::optional<Vector3> Plane::getIntersection(Ray ray)
{
    const Vector3& origin = ray.getOrigin();
    const Vector3& direction = ray.getDirection();

    double num = origin.x() * m_coordinates.x() + origin.y() * m_coordinates.y() + origin.z() * m_coordinates.z();

    double den =
            direction.x() * m_coordinates.x() + direction.y() * m_coordinates.y() + direction.z() * m_coordinates.z();

    if (den == 0)
        return std::nullopt;

    double t = (m_d - num) / den;

    Vector3 intersection = direction * t + origin;

    if ((direction.x() != 0 && (intersection.x() - origin.x()) / direction.x() < 0) ||
        (direction.y() != 0 && (intersection.y() - origin.y()) / direction.y() < 0) ||
        (direction.z() != 0 && (intersection.z() - origin.z()) / direction.z() < 0))
        return std::nullopt;

    return intersection;
}

std::optional<Ray> Plane::getSecondaryRay(Vector3 intersectionPoint, Vector3 originLight)
{
    return Ray(intersectionPoint, originLight - intersectionPoint, SECONDARY);
}

std::optional<Vector3> Plane::getRefractedIntersection(Ray ray)
{
    return getIntersection(ray);
}

Vector3 Plane::getNormal([[maybe_unused]] const Vector3& intersectionPoint)
{
    return m_coordinates;
}
