#include "Ray.h"

Ray::Ray(const Vector3& origin, const Vector3& direction, RayType type)
    : m_type(type),
      m_direction(direction),
      m_origin(origin)
{
}

RayType Ray::getType() const
{
    return m_type;
}

void Ray::setType(RayType type)
{
    m_type = type;
}

Vector3 Ray::getDirection() const
{
    return m_direction;
}

void Ray::setDirection(const Vector3& direction)
{
    m_direction = direction;
}

Vector3 Ray::getOrigin() const
{
    return m_origin;
}

void Ray::setOrigin(const Vector3& origin)
{
    m_origin = origin;
}
