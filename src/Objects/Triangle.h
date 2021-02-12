#ifndef H_RAYTRACING_TRIANGLE_H
#define H_RAYTRACING_TRIANGLE_H

#include "Object.h"

/**
 * @class Triangle
 * @brief Class that manage the triangle.
 *
 * This class provides information about the triangle object and the intersection point.
 *
 * @see Object, Vector3, Matrix, Color
 */
class Triangle : public Object
{
public:
    /**
     * @brief Constructor that initialize the triangle object.
     *
     * @param material    The object's material.
     * @param coordinates The coordinates of the triangle
     * @param color       The triangle's color
     * @param originA     The first point A
     * @param originB     The second point B
     * @param originC     The third point C
     */
    Triangle(Material material, const Color& color, Vector3 originA, Vector3 originB, Vector3 originC);

    /**
     * @brief Constructor that initialize the triangle object.
     *
     * @param material    The object's material.
     * @param coordinates The coordinates of the triangle
     * @param color       The triangle's color
     * @param originA     The first point A
     * @param originB     The second point B
     * @param originC     The third point C
     * @param normal      The normal of the triangle
     */
    Triangle(Material material, const Color& color, Vector3 originA, Vector3 originB, Vector3 originC, Vector3 normal);

    /**
     * @brief Method to get the intersection point with a ray and the triangle.
     *
     * @param ray The ray
     *
     * @return The intersection point if there is an intersection, nothing otherwise.
     */
    std::optional<Vector3> getIntersection(const Ray& ray) const override;

    /**
     * @brief Get the secondary ray from an intersection and origin point if there is an intersection.
     *
     * @param intersectionPoint The intersection point with the primary ray.
     * @param originLight       The origin point of the light.
     *
     * @return Returns the secondary ray if there is an intersection, nothing otherwise.
     */
    std::optional<Ray> getSecondaryRay(const Vector3& intersectionPoint, const Vector3& originLight) const override;

    /**
     * @brief Method to calculate the normal vector.
     *
     * @param intersectionPoint The intersection between the primary ray and the object.
     *
     * @return Returns the normal vector.
     */
    Vector3 getNormal([[maybe_unused]] const Vector3& intersectionPoint) const override;

    bool isInTriangle(const Vector3& intersectionPoint) const;

    /**
     * @brief Method using Heron's formula to calculate an area.
     *
     * @param a The first point
     * @param b The second point
     * @param c The third point
     *
     * @return Returns a double that represent the area of the triangle.
     */
    static double getArea(const Vector3& a, const Vector3& b, const Vector3& c);

private:
    /**
     * The vector to the first point A
     */
    Vector3 m_originA;

    /**
     * The vector to the second point B
     */
    Vector3 m_originB;

    /**
     * The vector to the third point C
     */
    Vector3 m_originC;

    /**
     * The normal vector to the triangle
     */
    Vector3 m_normal;
};

#endif //H_RAYTRACING_TRIANGLE_H
