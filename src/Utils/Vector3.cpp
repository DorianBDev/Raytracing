#include "Vector3.h"

#include "Utils.h"

#include <cmath>

Vector3::Vector3() : Matrix(1, 3)
{
}

Vector3::Vector3(double x, double y, double z) : Matrix(1, 3)
{
    setX(x);
    setY(y);
    setZ(z);
}

Vector3::Vector3(const Vector3& vector) : Matrix(1, 3)
{
    Matrix::fill(vector);
}

Vector3::Vector3(Vector3&& vector) noexcept : Matrix(std::move(vector))
{
}

Vector3::Vector3(const Matrix& matrix) : Matrix(1, 3)
{
    if (matrix.getRowCount() == 1 && matrix.getColumnCount() == 3)
    {
        *this = matrix;
    }
    else if (matrix.getRowCount() == 3 && matrix.getColumnCount() == 1)
    {
        *this = Matrix::transposed(matrix);
    }
    else if (matrix.getRowCount() != 1 || matrix.getColumnCount() != 3)
        throw Exception::Matrix::NotVector3("Can't initialize a Vector3 with this size (!= (1,3)).");
}

Vector3::Vector3(Matrix&& matrix) : Matrix(1, 3)
{
    if (matrix.getRowCount() == 1 && matrix.getColumnCount() == 3)
    {
        *this = std::move(matrix);
    }
    else if (matrix.getRowCount() == 3 || matrix.getColumnCount() == 1)
    {
        *this = Matrix::transposed(matrix);
    }
    else if (matrix.getRowCount() != 1 || matrix.getColumnCount() != 3)
        throw Exception::Matrix::NotVector3("Can't initialize a Vector3 with this size (!= (1,3)).");
}

Vector3::Vector3(const std::initializer_list<double>& initializerList) : Matrix(1, 3)
{
    fill(initializerList);
}

void Vector3::setX(double value)
{
    matrix(0, 0) = value;
}

void Vector3::setY(double value)
{
    matrix(0, 1) = value;
}

void Vector3::setZ(double value)
{
    matrix(0, 2) = value;
}

double Vector3::distance(const Vector3& vector)
{
    double x = pow2(matrix(0, 0) - vector.matrix(0, 0));
    double y = pow2(matrix(0, 1) - vector.matrix(0, 1));
    double z = pow2(matrix(0, 2) - vector.matrix(0, 2));

    return std::sqrt(x + y + z);
}

Vector3& Vector3::operator=(const Matrix& matrix)
{
    if (!isVector3(matrix))
        throw Exception::Matrix::NotVector3("The matrix can't be cast to a Vector3.");

    allocate(1, 3);
    Matrix::fill(matrix);

    return *this;
}

Vector3& Vector3::operator=(const Vector3& vector)
{
    if (this == &vector)
        return *this;

    allocate(1, 3);

    setX(vector.x());
    setY(vector.y());
    setZ(vector.z());

    return *this;
}

Vector3& Vector3::operator=(Matrix&& matrix) noexcept(false)
{
    if (!isVector3(matrix))
        throw Exception::Matrix::NotVector3("Can't initialize a Vector3 with this size (!= (1,3)).");

    MOVE(matrix);

    return *this;
}

Vector3& Vector3::operator=(Vector3&& vector) noexcept
{
    if (this == &vector)
        return *this;

    MOVE(vector);

    return *this;
}

void Vector3::fill(const std::initializer_list<double>& initializerList)
{
    std::size_t column = 0;
    for (const auto& value : initializerList)
    {
        if (column >= 3)
            throw Exception::Vector3::WrongInitializerList();

        matrix(0, column) = value;
        column++;
    }
}

bool isVector3(const Matrix& matrix)
{
    return (matrix.getRowCount() == 1 && matrix.getColumnCount() == 3);
}