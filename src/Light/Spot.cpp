#include "Spot.h"
Spot::Spot(double intensity, const Vector3& origin, const Vector3& direction, double angle)
    : Light(intensity),
      m_origin(origin),
      m_direction(direction),
      m_angle(angle * pi / 180)
{
}

bool Spot::isEnLight(Ray intersection)
{
    if (intersection.getType() != SECONDARY)
        return false;
    // See with all the objects if there is an interception with the ray

    intersection.setDirection((intersection.getDirection() * -1).toVector3());

    double cosA =
            (intersection.getOrigin().x() * m_direction.x() + intersection.getOrigin().y() * m_direction.y() +
             intersection.getOrigin().z() * m_direction.z()) /
            std::sqrt((std::pow(intersection.getOrigin().x(), 2) + std::pow(intersection.getOrigin().y(), 2) +
                       std::pow(intersection.getOrigin().z(), 2)) *
                      (std::pow(m_direction.x(), 2) + std::pow(m_direction.y(), 2) + std::pow(m_direction.z(), 2)));

    double angle = std::acos(cosA);

    double padding = 0.001;
    // Padding in case of comparison between two double that aren't exact values
    return angle <= m_angle + padding;
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
