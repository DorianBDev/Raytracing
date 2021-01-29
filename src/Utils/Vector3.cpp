#include "Vector3.h"

Vector3::Vector3() : Matrix(1, 3)
{
}

Vector3::Vector3(const Vector3& vector) : Matrix(1, 3)
{
}

Vector3::Vector3(const Matrix& matrix) : Matrix(matrix)
{
    if (matrix.getRowCount() == 3 && matrix.getColumnCount() == 1)
    {
        allocate(1, 3);
        Matrix::fill(Matrix::transposed(matrix));
    }
    else if (matrix.getRowCount() != 1 || matrix.getColumnCount() != 3)
        throw std::runtime_error("Wrong matrix size to initialize a Vector3.");
}

Vector3::Vector3(const Matrix&& matrix) : Matrix(matrix)
{
    if (matrix.getRowCount() == 3 || matrix.getColumnCount() == 1)
    {
        allocate(1, 3);
        Matrix::fill(Matrix::transposed(matrix));
    }
    else if (matrix.getRowCount() != 1 || matrix.getColumnCount() != 3)
        throw std::runtime_error("Wrong matrix size to initialize a Vector3.");
}

Vector3::Vector3(const std::initializer_list<double>& initializerList) : Matrix(1, 3)
{
    fill(initializerList);
}

double Vector3::x() const
{
    return value(0, 0);
}

double Vector3::y() const
{
    return value(0, 1);
}

double Vector3::z() const
{
    return value(0, 2);
}

void Vector3::setX(double value)
{
    setValue(0, 0, value);
}

void Vector3::setY(double value)
{
    setValue(0, 1, value);
}

void Vector3::setZ(double value)
{
    setValue(0, 2, value);
}

void Vector3::fill(const std::initializer_list<double>& initializerList)
{
    std::size_t column = 0;
    for (const auto& value : initializerList)
    {
        if (column >= 3)
            throw std::runtime_error("Wrong initializer list.");

        setValue(0, column, value);
        column++;
    }
}
