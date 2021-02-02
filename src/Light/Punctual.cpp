#include "Punctual.h"
Punctual::Punctual(double intensity, const Vector3& origin) : Light(intensity), m_origin(origin)
{
}

bool Punctual::isEnLight(Ray intersection)
{
    return intersection.getType() == SECONDARY;
}

std::optional<Vector3> Punctual::getOrigin(Ray intersection)
{
    if (intersection.getType() != SECONDARY)
        return std::nullopt;

    return m_origin;
}

std::optional<Vector3> Punctual::getDirection(Ray intersection)
{
    return (m_origin - intersection.getOrigin()).toVector3();
}
