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
     * @param coordinates Coordinates for the object.
     * @param color       Object's color.
     */
    Object(const Matrix& coordinates, Color color);

    /**
     * @brief Check if the ray intersect with the object, if this is the case it will return the intersection point.
     *
     * @param ray The ray to check the collision with.
     *
     * @return Returns the intersection point if there is an intersection, nothing otherwise.
     */
    virtual std::optional<Vector3> getIntersection(Ray ray) = 0;

    /**
     * @brief Method.
     *
     * This method change the coordinates of the object.
     *
     * @param coordinates Coordinates for the object.
     */
    void setCoordinates(const Matrix& coordinates);

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
     * This method return the coordinates of the object.
     *
     * @param coordinates Coordinates for the object.
     *
     * @return Returns the object's coordinates.
     */
    Matrix getCoordinates();

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
     * The object's coordinates.
     */
    Matrix m_coordinates;

    /**
     * The object's color.
     */
    Color m_color;
};

#endif //RAYTRACING_OBJECT_H
