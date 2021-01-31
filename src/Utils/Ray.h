#ifndef H_RAYTRACING_RAY_H
#define H_RAYTRACING_RAY_H

#include "Vector3.h"

/**
 * @enum RayType
 * @brief Store the type of a ray.
 */
enum RayType
{
    PRIMARY,  /*!< Primary ray (for intersections). */
    SECONDARY /*!< Secondary ray (for lightning). */
};

/**
 * @class Ray
 * @brief Describe a ray object.
 */
class Ray
{
public:
    /**
     * @brief Create a Ray object.
     *
     * @param origin    The origin point of the ray.
     * @param direction The direction of the ray.
     * @param type      The type of the ray.
     *
     * @see RayType
     */
    Ray(const Vector3& origin, const Vector3& direction, RayType type);

    /**
     * @brief Get the type of the ray.
     *
     * @return Returns the type of the ray.
     *
     * @see RayType
     */
    RayType getType() const;

    /**
     * @brief Set the ray type.
     *
     * @param type The new ray's type.
     *
     * @see RayType
     */
    void setType(RayType type);

    /**
     * @brief Get the direction of the ray.
     *
     * @return Returns the direction of the ray.
     */
    Vector3 getDirection() const;

    /**
     * @brief Set the direction of the ray.
     *
     * @param direction The new ray's direction.
     */
    void setDirection(const Vector3& direction);

    /**
     * @brief Get the ray's origin.
     *
     * @return Returns the ray's origin.
     */
    Vector3 getOrigin() const;

    /**
     * @brief Set the ray's origin.
     *
     * @param origin The new ray's origin.
     */
    void setOrigin(const Vector3& origin);

    /////////////////////////////////////////////////////////////////////
    /// Operators
    /////////////////////////////////////////////////////////////////////

    bool operator==(const Ray& ray) const;
    bool operator!=(const Ray& ray) const;

private:
    RayType m_type = PRIMARY;
    Vector3 m_direction;
    Vector3 m_origin;
};

#endif //H_RAYTRACING_RAY_H
