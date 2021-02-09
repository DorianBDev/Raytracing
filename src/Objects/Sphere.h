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
    Sphere(const Color& color, Vector3 coordinates, double radius);

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

    /**
     * @brief Check if the ray intersect with the object, if this is the case it will return the intersection point.
     *
     * @param ray The ray to check the collision with.
     *
     * @return Returns the second intersection point.
     */
    std::optional<Vector3> getRefractedIntersection(Ray ray) override;

    /**
     * @brief Method to calculate the normal vector.
     *
     * @param intersectionPoint The intersection between the primary ray and the object.
     *
     * @return Returns the normal vector.
     */
    Vector3 getNormal(const Vector3& intersectionPoint) override;

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