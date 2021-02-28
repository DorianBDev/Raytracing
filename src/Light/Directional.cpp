#include "Directional.h"

#include "Utils/Math.h"

#include <utility>

Directional::Directional(double intensity, const Color& color, Vector3 originA, Vector3 originB, Vector3 direction)
    : Light(intensity, color),
      m_originA(std::move(originA)),
      m_originB(std::move(originB)),
      m_direction(std::move(direction))
{
}

bool Directional::isEnLight(const Vector3& origin) const
{
    Vector3 ab = m_originB - m_originA;

    const Vector3& direction = m_direction;

    double den = ab.x() * direction.y() - ab.y() * direction.x();

    // Verify if the vector aren't parallel
    if (den == 0)
    {
        std::cout << den << std::endl;
        return false;
    }

    double x = -((m_originA.x() - origin.x()) * direction.y() - (m_originA.y() - origin.y()) * direction.x()) / den;

    double m = -((origin.y() - m_originA.y()) * ab.x() - (origin.x() - m_originA.x()) * ab.y()) / den;

    // Verify if it is in the range of originA and originB
    if (x < 0 || x > 1)
        return false;

    // 3D validation
    if ((ab.z() * x + m_originA.z() != origin.z() + direction.z() * m) &&
        !areDoubleApproximatelyEqual(ab.z() * x + m_originA.z(), origin.z() + direction.z() * m, 0.5))
        return false;

    return true;
}

std::optional<Vector3> Directional::getOrigin(const Vector3& origin) const
{
    Vector3 ab = m_originB - m_originA;

    const Vector3& direction = m_direction;

    double den = ab.x() * direction.y() - ab.y() * direction.x();

    // Verify if the vector aren't parallel
    if (den == 0)
        return std::nullopt;

    double x = -((m_originA.x() - origin.x()) * direction.y() - (m_originA.y() - origin.y()) * direction.x()) / den;

    double m = -((origin.y() - m_originA.y()) * ab.x() - (origin.x() - m_originA.x()) * ab.y()) / den;

    // Verify if it is in the range of originA and originB
    if (x < 0 || x > 1)
        return std::nullopt;

    // 3D validation
    if ((ab.z() * x + m_originA.z() != origin.z() + direction.z() * m) &&
        !areDoubleApproximatelyEqual(ab.z() * x + m_originA.z(), origin.z() + direction.z() * m, 0.5))
        return std::nullopt;

    return direction * m + origin;
}

std::optional<Vector3> Directional::getDirection(const Vector3& origin) const
{
    return m_direction - origin;
}
