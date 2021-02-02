#include "Directional.h"

Directional::Directional(double intensity, const Vector3& originA, const Vector3& originB, const Vector3& direction)
    : Light(intensity),
      m_originA(originA),
      m_originB(originB),
      m_direction(direction)
{
}

bool Directional::isEnLight(Ray intersection)
{
    if (intersection.getType() != SECONDARY)
        return false;

    Vector3 ab = (m_originB - m_originA).toVector3();
    intersection.setDirection((m_direction * -1).toVector3());

    double den = ab.x() * intersection.getDirection().y() - ab.y() * intersection.getDirection().x();

    // Verify if the vector aren't parallel
    if (den == 0)
        return false;

    double x = -((m_originA.x() - intersection.getOrigin().x()) * intersection.getDirection().y() -
                 (m_originA.y() - intersection.getOrigin().y()) * intersection.getDirection().x()) /
               den;

    double m = -((intersection.getOrigin().y() - m_originA.y()) * ab.x() -
                 (intersection.getOrigin().x() - m_originA.x()) * ab.y()) /
               den;

    // Verify if it is in the range of originA and originB
    if (x < 0 || x > 1)
        return false;

    // 3D validation
    if (ab.z() * x + m_originA.z() != intersection.getOrigin().z() + intersection.getDirection().z() * m)
        return false;

    // Verify if the direction have the same orientation
    if (m_direction.x() / (intersection.getOrigin() - m_direction).toVector3().x() < 0)
        return false;

    return true;
}

std::optional<Vector3> Directional::getOrigin(Ray intersection)
{
    if (intersection.getType() != SECONDARY)
        return std::nullopt;

    Vector3 ab = (m_originB - m_originA).toVector3();
    intersection.setDirection((m_direction * -1).toVector3());

    double den = ab.x() * intersection.getDirection().y() - ab.y() * intersection.getDirection().x();

    // Verify if the vector aren't parallel
    if (den == 0)
        return std::nullopt;

    //std::cout << "pass 1" << std::endl;

    // y = ab * x +  m_originA
    double x = -((m_originA.x() - intersection.getOrigin().x()) * intersection.getDirection().y() -
                 (m_originA.y() - intersection.getOrigin().y()) * intersection.getDirection().x()) /
               den;

    double m = -((intersection.getOrigin().y() - m_originA.y()) * ab.x() -
                 (intersection.getOrigin().x() - m_originA.x()) * ab.y()) /
               den;

    // Verify if it is in the range of originA and originB
    if (x < 0 || x > 1)
        return std::nullopt;

    // 3D validation
    if (ab.z() * x + m_originA.z() != intersection.getOrigin().z() + intersection.getDirection().z() * m)
        return std::nullopt;

    // Orientation validation
    if (m_direction.x() / (intersection.getOrigin() - m_direction).toVector3().x() < 0)
        return std::nullopt;

    return (intersection.getDirection() * m + intersection.getOrigin()).toVector3();
}

std::optional<Vector3> Directional::getDirection(Ray intersection)
{
    return (m_direction - intersection.getOrigin()).toVector3();
}
