#include "Ray.h"

#include <utility>

Ray::Ray(Vector3 origin, Vector3 direction, RayType type)
    : m_type(type),
      m_direction(std::move(direction)),
      m_origin(std::move(origin))
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

const Vector3& Ray::getDirection() const
{
    return m_direction;
}

void Ray::setDirection(const Vector3& direction)
{
    m_direction = direction;
}

const Vector3& Ray::getOrigin() const
{
    return m_origin;
}

void Ray::setOrigin(const Vector3& origin)
{
    m_origin = origin;
}

bool Ray::operator==(const Ray& ray) const
{
    return !(!Matrix::areApproximatelyEqual(ray.getOrigin(), getOrigin()) ||
             !Matrix::areApproximatelyEqual(ray.getDirection(), getDirection()) || ray.getType() != getType());
}

bool Ray::operator!=(const Ray& ray) const
{
    return !(*this == ray);
}