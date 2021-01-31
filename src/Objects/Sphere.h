#ifndef H_RAYTRACING_SPHERE_H
#define H_RAYTRACING_SPHERE_H

#include "Object.h"

#include <cmath>

/**
 * @class Sphere
 * @brief Class that manage the sphere.
 *
 * This class provides information about the sphere object and the intersection point with a radius.
 *
 * @see Object, Vector3, Matrix, Color
 */
class Sphere : Object
{
public:
    /**
     * @brief Constructor that initialize the sphere object.
     *
     * @param coordinates Coordinates of the sphere's center
     * @param color       The color of the sphere
     * @param radius      The radius of the sphere
     */
    Sphere(const Vector3& coordinates, Color color, double radius);

    /**
     * @brief Method to get the intersection point with a ray and the sphere.
     *
     * @param ray The ray
     *
     * @return The intersection point if there is an intersection, nothing otherwise.
     */
    std::optional<Vector3> getIntersection(Ray ray) override;

    /**
     * @brief Get the secondary ray from a primary ray, if there is an intersection.
     *
     * @param ray The primary ray to use.
     *
     * @return Returns the secondary ray if there is an intersection, nothing otherwise.
     */
    std::optional<Ray> getSecondaryRay(Ray ray) override;

private:
    /**
     * The radius of the sphere.
     */
    double m_radius;
};

#endif //H_RAYTRACING_SPHERE_H