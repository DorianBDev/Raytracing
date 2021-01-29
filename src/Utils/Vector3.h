#ifndef H_RAYTRACING_VECTOR3_H
#define H_RAYTRACING_VECTOR3_H

#include "Matrix.h"

/**
 * @class Vector3
 * @brief 3D Vector.
 *
 * @see Matrix
 */
class Vector3 : public Matrix
{
public:
    /**
     * @brief Create an empty 3D vector.
     */
    Vector3();

    /**
     * @brief Create a 3D vector from another one.
     *
     * @param vector The vector to copy from.
     */
    Vector3(const Vector3& vector);

    /**
     * @brief Create a 3D vector from a matrix (1,3).
     *
     * @param matrix The matrix to copy from.
     */
    explicit Vector3(const Matrix& matrix);
    explicit Vector3(const Matrix&& matrix);

    /**
     * @brief Create a 3D vector from an initialized list.
     *
     * It will take the form 'Vector3({ x, y, z });'.
     *
     * @param initializerList The initialized list.
     */
    Vector3(const std::initializer_list<double>& initializerList);

    /**
     * @brief Get the x coordinate of the 3D vector.
     *
     * @return Returns the x coordinate of the 3D vector.
     */
    double x() const;

    /**
     * @brief Get the y coordinate of the 3D vector.
     *
     * @return Returns the y coordinate of the 3D vector.
     */
    double y() const;

    /**
     * @brief Get the z coordinate of the 3D vector.
     *
     * @return Returns the z coordinate of the 3D vector.
     */
    double z() const;

    /**
     * @brief Set the value of the x coordinate of the 3D vector.
     *
     * @param value The new value of the x coordinate.
     */
    void setX(double value);

    /**
     * @brief Set the value of the y coordinate of the 3D vector.
     *
     * @param value The new value of the y coordinate.
     */
    void setY(double value);

    /**
     * @brief Set the value of the z coordinate of the 3D vector.
     *
     * @param value The new value of the z coordinate.
     */
    void setZ(double value);

protected:
    /**
     * @brief Fill the matrix from an initializer list.
     *
     * @param initializerList The initializer list.
     */
    void fill(const std::initializer_list<double>& initializerList);
};

#endif //H_RAYTRACING_VECTOR3_H
