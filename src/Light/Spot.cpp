#include "Spot.h"
Spot::Spot(double intensity, const Vector3& origin, const Vector3& direction, double angle)
    : Light(intensity),
      m_origin(origin),
      m_direction(direction),
      m_angle(angle)
{
}

bool Spot::isEnLight(Ray intersection)
{
    if (intersection.getType() != SECONDARY)
        return false;
    // See with all the objects if there is an interception with the ray

    intersection.setDirection((intersection.getDirection() * -1).toVector3());

    double cosA =
            (intersection.getDirection().x() * m_direction.x() + intersection.getDirection().y() * m_direction.y() +
             intersection.getDirection().z() * m_direction.z()) /
            std::sqrt((std::pow(intersection.getDirection().x(), 2) + std::pow(intersection.getDirection().y(), 2) +
                       std::pow(m_direction.z(), 2)) *
                      (std::pow(m_direction.x(), 2) + std::pow(m_direction.y(), 2) + std::pow(m_direction.z(), 2)));

    double angle = std::acos(cosA);

    return angle <= m_angle;
}

std::optional<Vector3> Spot::getOrigin(Ray intersection)
{
    if (intersection.getType() != SECONDARY)
        return std::nullopt;

    return m_origin;
}

std::optional<Vector3> Spot::getDirection(Ray intersection)
{
    return (m_origin - intersection.getOrigin()).toVector3();
}
