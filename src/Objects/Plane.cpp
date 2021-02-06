#include "Plane.h"

Plane::Plane(const Vector3& coordinates, Color color, double d) : Object(coordinates, color), m_d(d)
{
}

std::optional<Vector3> Plane::getIntersection(Ray ray)
{
    if (ray.getType() != PRIMARY)
        return std::nullopt;

    Vector3 origin = ray.getOrigin();
    Vector3 direction = ray.getDirection();

    double num = origin.x() * this->getCoordinates().x() + origin.y() * this->getCoordinates().y() +
                 origin.z() * this->getCoordinates().z();

    double den = direction.x() * this->getCoordinates().x() + direction.y() * this->getCoordinates().y() +
                 direction.z() * this->getCoordinates().z();

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
