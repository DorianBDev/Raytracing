#include "Punctual.h"

#include <utility>

Punctual::Punctual(double intensity, Vector3 origin) : Light(intensity), m_origin(std::move(origin))
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
