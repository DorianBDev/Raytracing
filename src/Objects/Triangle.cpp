#include "Triangle.h"

#include "Plane.h"

#include <utility>

Triangle::Triangle(Color color, Vector3 originA, Vector3 originB, Vector3 originC)
    : Object(color),
      m_originA(std::move(originA)),
      m_originB(std::move(originB)),
      m_originC(std::move(originC))
{
}

std::optional<Vector3> Triangle::getIntersection(Ray ray)
{
    if (ray.getType() != PRIMARY)
        return std::nullopt;

    // We find the plane equation
    Vector3 u = m_originC - m_originA;
    Vector3 v = m_originB - m_originA;

    Vector3 coordinates = Matrix::vectProduct(u, v);
    double d = coordinates.x() * m_originA.x() + coordinates.y() * m_originA.y() + coordinates.z() * m_originA.z();

    Color color{};
    Plane plane(color, {coordinates.x(), coordinates.y(), coordinates.z()}, d);

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

std::optional<Ray> Triangle::getSecondaryRay(Vector3 intersectionPoint, Vector3 originLight)
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
