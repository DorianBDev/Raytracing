#include "Spot.h"

#include "Utils/Utils.h"

#include <utility>

Spot::Spot(double intensity, Color color, Vector3 origin, Vector3 direction, double angle)
    : Light(intensity, color),
      m_origin(std::move(origin)),
      m_direction(std::move(direction)),
      m_angle(angle * pi / 180)
{
}

bool Spot::isEnLight(Vector3 origin)
{
    // See with all the objects if there is an interception with the ray
    double num = origin.x() * m_direction.x() + origin.y() * m_direction.y() + origin.z() * m_direction.z();

    double den1 = pow2(origin.x()) + pow2(origin.y()) + pow2(origin.z());

    double den2 = pow2(m_direction.x()) + pow2(m_direction.y()) + pow2(m_direction.z());

    double cosA = num / std::sqrt(den1 * den2);
    double angle = std::acos(cosA);

    double padding = 0.001;
    // Padding in case of comparison between two double that aren't exact values
    return angle <= m_angle + padding;
}

std::optional<Vector3> Spot::getOrigin([[maybe_unused]] Vector3 origin)
{
    return m_origin;
}

std::optional<Vector3> Spot::getDirection(Vector3 origin)
{
    return m_origin - origin;
}
