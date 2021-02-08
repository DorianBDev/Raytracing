#include "Punctual.h"

#include <utility>

Punctual::Punctual(double intensity, const Color& color, Vector3 origin)
    : Light(intensity, color),
      m_origin(std::move(origin))
{
}

bool Punctual::isEnLight([[maybe_unused]] const Vector3& origin) const
{
    return true;
}

std::optional<Vector3> Punctual::getOrigin([[maybe_unused]] const Vector3& origin) const
{
    return m_origin;
}

std::optional<Vector3> Punctual::getDirection(const Vector3& origin) const
{
    return m_origin - origin;
}
