#ifndef H_RAYTRACING_PLANE_H
#define H_RAYTRACING_PLANE_H

#include "Object.h"

/**
 * @class Plane
 * @brief Class that manage the plane.
 *
 * This class provides information about the plane object and the intersection point.
 *
 * @see Object, Vector3, Matrix, Color
 */
class Plane : public Object
{
public:
    /**
     * @brief Constructor to initialize a plane object.
     *
     * @param color       The color of the plane
     * @param coordinates The equation of the plane
     * @param d           The const of the plane
     */
    Plane(const Color& color, Vector3 coordinates, double d);

    /**
     * @brief Method to get the intersection point with a ray and the plane.
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
     * @brief Method to calculate the normal vector.
     *
     * @param intersectionPoint The intersection between the primary ray and the object.
     *
     * @return Returns the normal vector.
     */
    Vector3 getNormal([[maybe_unused]] const Vector3& intersectionPoint) override;

private:
    /**
     * The coordinates of the plane.
     */
    Vector3 m_coordinates;

    /**
     * The const of the plane.
     */
    double m_d;
};

#endif //H_RAYTRACING_PLANE_H
