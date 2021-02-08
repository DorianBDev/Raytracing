#ifndef H_RAYTRACING_OBJECT_H
#define H_RAYTRACING_OBJECT_H

#include "Utils/Color.h"
#include "Utils/Ray.h"
#include "Utils/Vector3.h"

#include <optional>

/**
 * @class Object
 * @brief Class that manage the object.
 *
 * Class that manage the object.
 * Manage the color, the coordinates of the object.
 *
 * @see Matrix, Color
 */
class Object
{
public:
    /**
     * @brief Constructor.
     *
     * This constructor initialize the object.
     *
     * @param color       Object's color.
     */
    explicit Object(Color color);
    virtual ~Object() = default;

    /**
     * @brief Check if the ray intersect with the object, if this is the case it will return the intersection point.
     *
     * @param ray The ray to check the collision with.
     *
     * @return Returns the intersection point if there is an intersection, nothing otherwise.
     */
    virtual std::optional<Vector3> getIntersection(Ray ray) = 0;

    /**
     * @brief Get the secondary ray from an intersection and origin point if there is an intersection.
     *
     * @param intersectionPoint The intersection point with the primary ray.
     * @param originLight       The origin point of the light.
     *
     * @return Returns the secondary ray if there is an intersection, nothing otherwise.
     */
    virtual std::optional<Ray> getSecondaryRay(Vector3 intersectionPoint, Vector3 originLight) = 0;

    /**
     * @brief Method to calculate the normal vector.
     *
     * @param intersectionPoint The intersection between the primary ray and the object.
     *
     * @return Returns the normal vector.
     */
    virtual Vector3 getNormal(const Vector3& intersectionPoint) = 0;

    /**
     * @brief Method.
     *
     * This method change the color of the object.
     *
     * @param color Object's color.
     */
    void setColor(Color color);

    /**
     * @brief Method.
     *
     * This method return the color of the object.
     *
     * @param color Object's color.
     *
     * @return Returns the object's color.
     */
    Color getColor();

private:
    /**
     * The object's color.
     */
    Color m_color;
};

#endif //RAYTRACING_OBJECT_H
