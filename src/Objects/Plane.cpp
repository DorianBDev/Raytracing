#include "Plane.h"

Plane::Plane(const Vector3& coordinates, Color color, double d) : Object(coordinates, color), m_d(d)
{
}

std::optional<Vector3> Plane::getIntersection(Ray ray)
{
    if (ray.getType() != PRIMARY)
        return std::nullopt;

    double num = ray.getOrigin().x() * this->getCoordinates().x() + ray.getOrigin().y() * this->getCoordinates().y() +
                 ray.getOrigin().z() * this->getCoordinates().z();

    double den = ray.getDirection().x() * this->getCoordinates().x() +
                 ray.getDirection().y() * this->getCoordinates().y() +
                 ray.getDirection().z() * this->getCoordinates().z();

    if (den == 0)
        return std::nullopt;

    double t = (m_d - num) / den;

    Vector3 intersection = (ray.getDirection() * t + ray.getOrigin()).toVector3();

    if ((intersection.x() - ray.getOrigin().x()) / ray.getDirection().x() < 0)
        return std::nullopt;

    return intersection;
}

std::optional<Ray> Plane::getSecondaryRay(Vector3 intersectionPoint, Vector3 originLight)
{
    return Ray(intersectionPoint, (originLight - intersectionPoint).toVector3(), SECONDARY);
}
