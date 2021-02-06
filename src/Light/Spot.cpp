#include "Spot.h"

#include <utility>

Spot::Spot(double intensity, Vector3 origin, Vector3 direction, double angle)
    : Light(intensity),
      m_origin(std::move(origin)),
      m_direction(std::move(direction)),
      m_angle(angle * pi / 180)
{
}

bool Spot::isEnLight(Ray intersection)
{
    if (intersection.getType() != SECONDARY)
        return false;
    // See with all the objects if there is an interception with the ray

    Vector3 origin = intersection.getOrigin();

    double num = origin.x() * m_direction.x() + origin.y() * m_direction.y() + origin.z() * m_direction.z();

    double den1 = std::pow(origin.x(), 2) + std::pow(origin.y(), 2) + std::pow(origin.z(), 2);

    double den2 = std::pow(m_direction.x(), 2) + std::pow(m_direction.y(), 2) + std::pow(m_direction.z(), 2);

    double cosA = num / std::sqrt(den1 * den2);
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
    return m_origin - intersection.getOrigin();
}
