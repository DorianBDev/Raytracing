#include "Sphere.h"

Sphere::Sphere(const Vector3& coordinates, Color color, double radius) : Object(coordinates, color), m_radius(radius)
{
}

std::optional<Vector3> Sphere::getIntersection(Ray ray)
{
    double a = pow(ray.getDirection().x(), 2) + pow(ray.getDirection().y(), 2) + pow(ray.getDirection().z(), 2);

    double b = 2 * ((ray.getOrigin().x() - this->getCoordinates().x()) * ray.getDirection().x() +
                    (ray.getOrigin().y() - this->getCoordinates().y()) * ray.getDirection().y() +
                    (ray.getOrigin().z() - this->getCoordinates().z()) * ray.getDirection().z());

    double c = pow(ray.getOrigin().x() - this->getCoordinates().x(), 2) +
               pow(ray.getOrigin().y() - this->getCoordinates().y(), 2) +
               pow(ray.getOrigin().z() - this->getCoordinates().z(), 2) - pow(m_radius, 2);

    double discriminant = pow(b, 2) - 4 * a * c;

    Vector3 res;

    if (discriminant == 0)
    {
        // One solution exist, it is a tangent point
        double t = -b / (2 * a);
        res = ray.getDirection() * t + ray.getOrigin();
        return res;
    }

    if (discriminant > 0)
    {
        double t1 = (-b - sqrt(discriminant)) / (2 * a);
        double t2 = (-b + sqrt(discriminant)) / (2 * a);

        if (t1 > 0)
        {
            res = ray.getDirection() * t1 + ray.getOrigin();
            return res;
        }

        if (t2 > 0)
        {
            res = ray.getDirection() * t2 + ray.getOrigin();
            return res;
        }
    }

    return std::nullopt;
}
std::optional<Ray> Sphere::getSecondaryRay(Ray ray)
{
    //Vector3 reflect = Matrix::reflection(ray.getDirection(), ray.getDirection());

    return std::optional<Ray>(ray);
}
