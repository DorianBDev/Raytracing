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
     * @brief Create an empty 3D vector.
     *
     * @param x The x coordinate value.
     * @param y The y coordinate value.
     * @param z The z coordinate value.
     */
    Vector3(double x, double y, double z);

    /**
     * @brief Create a 3D vector from another one.
     *
     * @param vector The vector to copy from.
     */
    Vector3(const Vector3& vector);

    /**
     * @brief Constructor by move.
     */
    Vector3(Vector3&& vector) noexcept;

    /**
     * @brief Create a 3D vector from a matrix (1,3).
     *
     * @param matrix The matrix to copy from.
     */
    Vector3(const Matrix& matrix); // NOLINT
    Vector3(Matrix&& matrix);      // NOLINT

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
    constexpr double x() const
    {
        return value(0, 0);
    }

    /**
     * @brief Get the y coordinate of the 3D vector.
     *
     * @return Returns the y coordinate of the 3D vector.
     */
    constexpr double y() const
    {
        return value(0, 1);
    }

    /**
     * @brief Get the z coordinate of the 3D vector.
     *
     * @return Returns the z coordinate of the 3D vector.
     */
    constexpr double z() const
    {
        return value(0, 2);
    }

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

    /**
     * @brief Euclidean distance between this and another vector.
     *
     * @param vector The other vector to use in the calculation.
     *
     * @return Returns the euclidean distance.
     */
    double distance(const Vector3& vector);

    Vector3& operator=(const Matrix& matrix);
    Vector3& operator=(const Vector3& vector);
    Vector3& operator=(Matrix&& matrix) noexcept(false);
    Vector3& operator=(Vector3&& vector) noexcept;

protected:
    /**
     * @brief Fill the vector with an initializer list.
     *
     * @param initializerList The initializer list.
     */
    void fill(const std::initializer_list<double>& initializerList);
};

/**
 * @brief Check if a matrix is a Vector3 (size of 1,3).
 *
 * @param matrix The matrix to test.
 *
 * @return Returns true if the matrix is a Vector3, false otherwise.
 */
bool isVector3(const Matrix& matrix);

#endif //H_RAYTRACING_VECTOR3_H
