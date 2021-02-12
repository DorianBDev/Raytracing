#ifndef H_RAYTRACING_MODEL_H
#define H_RAYTRACING_MODEL_H

#include "Object.h"
#include "Triangle.h"

#include <fstream>
#include <regex>
#include <sstream>
#include <string>
#include <vector>

/**
 * @class Model
 * @brief Class that manage the model object.
 *
 * Class that manage the model object.
 *
 * @see Matrix, Color, Object, Triangle
 */
class Model : public Object
{
public:
    /**
     * Constructor that initialize an model object.
     *
     * @param material    The object's material.
     * @param color       Object's color.
     * @param path        The path of the object's file.
     * @param coordinates The coordinates of the object.
     */
    Model(Material material, const Color& color, const std::string& path, const Vector3& coordinates, const Vector3& angle, double scale);

    /**
     * @brief Method to get the intersection point with a ray and the plane.
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

    /**
     * Method to split a string with a delimiter
     *
     * @param line      The line
     * @param delimiter The delimiter
     *
     * @return Returns the vector corresponding to the line of the obj file.
     */
    static Vector3 split(const std::string& line, char delimiter);

private:
    /**
     * Method that read the object file.
     *
     * @param path   The path of the .obj file.
     */
    void readFile(const std::string& path);

    /**
     * The triangle of the objects
     */
    std::vector<Triangle> m_triangle;

    const Vector3& m_origin;

    const Vector3& m_angle;

    double m_scale;
};

#endif //H_RAYTRACING_MODEL_H
