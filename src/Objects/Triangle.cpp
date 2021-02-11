#include "Triangle.h"

#include "Plane.h"

#include <utility>

Triangle::Triangle(Material material, const Color& color, Vector3 originA, Vector3 originB, Vector3 originC)
    : Object(material, color),
      m_originA(std::move(originA)),
      m_originB(std::move(originB)),
      m_originC(std::move(originC))
{
    Vector3 u = m_originC - m_originA;
    Vector3 v = m_originB - m_originA;

    m_normal = Matrix::vectProduct(u, v) * -1;
}

std::optional<Vector3> Triangle::getIntersection(const Ray& ray) const
{
    // We find the plane equation
    double d = m_normal.x() * m_originA.x() + m_normal.y() * m_originA.y() + m_normal.z() * m_originA.z();

    Plane plane(getMaterial(), getColor(), {m_normal.x(), m_normal.y(), m_normal.z()}, d);

    std::optional<Vector3> intersection = plane.getIntersection(ray);

    if (intersection == std::nullopt)
        return std::nullopt;

    // To verify if it is in the triangle
    double areaTotal = getArea(m_originA, m_originB, m_originC);
    double areaA = getArea(m_originA, m_originB, intersection.value());
    double areaB = getArea(m_originB, m_originC, intersection.value());
    double areaC = getArea(m_originA, m_originC, intersection.value());

    // The padding is necessary to compare two doubles
    double padding = 0.001;

    if ((areaA + areaB + areaC <= areaTotal + padding) && (areaA + areaB + areaC >= areaTotal - padding))
        return intersection;

    return std::nullopt;
}

std::optional<Ray> Triangle::getSecondaryRay(const Vector3& intersectionPoint, const Vector3& originLight) const
{
    return Ray(intersectionPoint, originLight - intersectionPoint, SECONDARY);
}

double Triangle::getArea(const Vector3& a, const Vector3& b, const Vector3& c)
{
    double ab = Matrix::getNorm(a - b);
    double bc = Matrix::getNorm(b - c);
    double ac = Matrix::getNorm(a - c);

    double p = (ab + bc + ac) / 2;
    return std::sqrt(p * (p - ab) * (p - bc) * (p - ac));
}

std::optional<Vector3> Triangle::getRefractedIntersection(const Ray& ray) const
{
    return getIntersection(ray);
}

Vector3 Triangle::getNormal([[maybe_unused]] const Vector3& intersectionPoint) const
{
    return m_normal;
}
