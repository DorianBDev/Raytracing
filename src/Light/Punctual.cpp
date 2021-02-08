#include "Punctual.h"

#include <utility>

Punctual::Punctual(double intensity, Color color, Vector3 origin) : Light(intensity, color), m_origin(std::move(origin))
{
}

bool Punctual::isEnLight([[maybe_unused]] Vector3 origin)
{
    return true;
}

std::optional<Vector3> Punctual::getOrigin([[maybe_unused]] Vector3 origin)
{
    return m_origin;
}

std::optional<Vector3> Punctual::getDirection(Vector3 origin)
{
    return m_origin - origin;
}
