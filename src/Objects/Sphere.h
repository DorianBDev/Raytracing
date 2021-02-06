#ifndef H_RAYTRACING_SPHERE_H
#define H_RAYTRACING_SPHERE_H

#include "Object.h"

/**
 * @class Sphere
 * @brief Class that manage the sphere.
 *
 * This class provides information about the sphere object and the intersection point with a radius.
 *
 * @see Object, Vector3, Matrix, Color
 */
class Sphere : public Object
{
public:
    /**
     * @brief Constructor that initialize the sphere object.
     *
     * @param color       The color of the sphere
     * @param coordinates Coordinates of the sphere's center
     * @param radius      The radius of the sphere
     */
    Sphere(Color color, Vector3 coordinates, double radius);

    /**
     * @brief Method to get the intersection point with a ray and the sphere.
     *
     * @param ray The ray
     *
     * @return The intersection point if there is an intersection, nothing otherwise.
     */
    std::optional<Vector3> getIntersection(Ray ray) override;

    /**
     * @brief Get the secondary ray from an intersection and origin point if there is an intersection.
     *
     * @param intersectionPoint The intersection point with the primary ray.
     * @param originLight       The origin point of the light.
     *
     * @return Returns the secondary ray if there is an intersection, nothing otherwise.
     */
    std::optional<Ray> getSecondaryRay(Vector3 intersectionPoint, Vector3 originLight) override;

private:
    /**
     * The coordinates of the sphere.
     */
    Vector3 m_coordinates;

    /**
     * The radius of the sphere.
     */
    double m_radius;
};

#endif //H_RAYTRACING_SPHERE_H