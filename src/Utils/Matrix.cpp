#include "Matrix.h"

#include "Vector3.h"

#include <cmath>

Matrix::Matrix(std::size_t rowCount, std::size_t columnCount) : m_rowCount(rowCount), m_columnCount(columnCount)
{
    allocate(rowCount, columnCount);
    fill(0);
}

Matrix::Matrix(std::size_t rowCount,
               std::size_t columnCount,
               const std::initializer_list<std::initializer_list<double>>& initializerList)
    : m_rowCount(rowCount),
      m_columnCount(columnCount)
{
    allocate(rowCount, columnCount);
    fill(initializerList);
}

Matrix::Matrix(std::size_t rowCount,
               std::size_t columnCount,
               const std::initializer_list<std::initializer_list<double>>&& initializerList)
    : m_rowCount(rowCount),
      m_columnCount(columnCount)
{
    allocate(rowCount, columnCount);
    fill(initializerList);
}

Matrix::Matrix(const Matrix& a) : m_rowCount(a.m_rowCount), m_columnCount(a.m_columnCount)
{
    allocate(m_rowCount, m_columnCount);
    fill(a);
}

Matrix::~Matrix()
{
    deallocate();
}

void Matrix::print() const
{
    if (m_columnCount == 0 || m_rowCount == 0)
    {
        throw std::runtime_error("The m_matrix isn't init");
    }

    for (std::size_t i = 0; i < m_rowCount; i++)
    {
        for (std::size_t j = 0; j < m_columnCount; j++)
        {
            std::cout << m_matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

double Matrix::value(std::size_t row, std::size_t column) const
{
    if (row >= m_rowCount || column >= m_columnCount)
        throw std::runtime_error("Wrong coordinates to get a value.");

    return m_matrix[row][column];
}

void Matrix::setValue(std::size_t row, std::size_t column, double value)
{
    if (row >= m_rowCount || column >= m_columnCount)
        throw std::runtime_error("Wrong coordinates to set a value.");

    m_matrix[row][column] = value;
}

std::size_t Matrix::getRowCount() const
{
    return m_rowCount;
}

std::size_t Matrix::getColumnCount() const
{
    return m_columnCount;
}

Vector3 Matrix::toVector3() const
{
    if (m_rowCount != 1 || m_columnCount != 3)
        throw std::runtime_error("Can't create Vector3 from a matrix != (1,3).");

    return Vector3(*this);
}

Matrix& Matrix::translate(const Matrix& a)
{
    *this = Matrix::translation(*this, a);
    return *this;
}

Matrix& Matrix::rotateX(double angle)
{
    *this = Matrix::rotationX(angle, *this);
    return *this;
}

Matrix& Matrix::rotateY(double angle)
{
    *this = Matrix::rotationY(angle, *this);
    return *this;
}

Matrix& Matrix::rotateZ(double angle)
{
    *this = Matrix::rotationZ(angle, *this);
    return *this;
}

Matrix& Matrix::scale(double x, double y, double z)
{
    *this = Matrix::scale(x, y, z, *this);
    return *this;
}

Matrix& Matrix::transpose()
{
    *this = Matrix::transposed(*this);
    return *this;
}

double Matrix::getNorm() const
{
    return Matrix::getNorm(*this);
}

Matrix& Matrix::normalize()
{
    *this = Matrix::normalize(*this);
    return *this;
}

Matrix& Matrix::invert()
{
    *this = Matrix::invert(*this);
    return *this;
}

double Matrix::determinant() const
{
    return Matrix::determinant(*this);
}

/////////////////////////////////////////////////////////////////////
/// Operators
/////////////////////////////////////////////////////////////////////

Matrix& Matrix::operator=(const Matrix& matrix)
{
    if (this == &matrix)
        return *this;

    allocate(matrix.m_rowCount, matrix.m_columnCount);
    Matrix::fill(matrix);

    return *this;
}

Matrix& Matrix::operator+=(const Matrix& matrix)
{
    *this = Matrix::addMatrix(*this, matrix);

    return *this;
}

Matrix& Matrix::operator-=(const Matrix& matrix)
{
    *this = Matrix::subMatrix(*this, matrix);

    return *this;
}

Matrix& Matrix::operator*=(const Matrix& matrix)
{
    *this = Matrix::matrixProduct(*this, matrix);

    return *this;
}

Matrix& Matrix::operator*=(double scalar)
{
    *this = Matrix::scalarProduct(*this, scalar);

    return *this;
}

Matrix Matrix::operator+(const Matrix& matrix) const
{
    return Matrix::addMatrix(*this, matrix);
}

Matrix Matrix::operator-(const Matrix& matrix) const
{
    return Matrix::subMatrix(*this, matrix);
}

Matrix Matrix::operator*(const Matrix& matrix) const
{
    return Matrix::matrixProduct(*this, matrix);
}

Matrix Matrix::operator*(double scalar) const
{
    return Matrix::scalarProduct(*this, scalar);
}

bool Matrix::operator==(const Matrix& matrix) const
{
    if (matrix.getRowCount() != m_rowCount || matrix.getColumnCount() != m_columnCount)
        return false;

    for (std::size_t row = 0; row < m_rowCount; row++)
    {
        for (std::size_t column = 0; column < m_columnCount; column++)
        {
            if (std::fabs(matrix.m_matrix[row][column] - m_matrix[row][column]) >
                std::numeric_limits<double>::epsilon())
                return false;
        }
    }

    return true;
}

bool Matrix::operator!=(const Matrix& matrix) const
{
    return !(*this == matrix);
}

/////////////////////////////////////////////////////////////////////
/// Static methods
/////////////////////////////////////////////////////////////////////

Matrix Matrix::addMatrix(const Matrix& a, const Matrix& b)
{
    if ((a.m_columnCount != b.m_columnCount) || (a.m_rowCount != b.m_rowCount))
    {
        throw std::runtime_error("The m_matrix haven't the same dimension");
    }

    Matrix c = Matrix(a.m_rowCount, a.m_columnCount);

    for (std::size_t i = 0; i < c.m_rowCount; i++)
    {
        for (std::size_t j = 0; j < c.m_columnCount; j++)
        {
            c.m_matrix[i][j] = a.m_matrix[i][j] + b.m_matrix[i][j];
        }
    }

    return c;
}

Matrix Matrix::subMatrix(const Matrix& a, const Matrix& b)
{
    if ((a.m_columnCount != b.m_columnCount) || (a.m_rowCount != b.m_rowCount))
    {
        throw std::runtime_error("The m_matrix haven't the same dimension");
    }

    Matrix c = Matrix(a.m_rowCount, a.m_columnCount);

    for (std::size_t i = 0; i < c.m_rowCount; i++)
    {
        for (std::size_t j = 0; j < c.m_columnCount; j++)
        {
            c.m_matrix[i][j] = a.m_matrix[i][j] - b.m_matrix[i][j];
        }
    }

    return c;
}

Matrix Matrix::scalarProduct(const Matrix& a, double scalar)
{
    if (a.m_columnCount == 0 || a.m_rowCount == 0)
    {
        throw std::runtime_error("The m_matrix isn't init");
    }

    Matrix c = Matrix(a.m_rowCount, a.m_columnCount);

    for (std::size_t i = 0; i < c.m_rowCount; i++)
    {
        for (std::size_t j = 0; j < c.m_columnCount; j++)
        {
            c.m_matrix[i][j] = a.m_matrix[i][j] * scalar;
        }
    }

    return c;
}

Matrix Matrix::matrixProduct(const Matrix& a, const Matrix& b)
{
    if (a.m_columnCount == 0 || a.m_columnCount != b.m_rowCount)
    {
        throw std::runtime_error("Problem with dimension to multiply the m_matrix");
    }

    Matrix c = Matrix(a.m_rowCount, b.m_columnCount);

    for (std::size_t i = 0; i < a.m_rowCount; i++)
    {
        for (std::size_t j = 0; j < b.m_columnCount; j++)
        {
            for (std::size_t k = 0; k < b.m_rowCount; k++)
            {
                c.m_matrix[i][j] = a.m_matrix[i][k] * b.m_matrix[k][j] + c.m_matrix[i][j];
            }
        }
    }

    return c;
}

Matrix Matrix::translation(const Matrix& a, const Matrix& b)
{
    /* check if it's Vec3 */
    if (a.m_columnCount == 1 && a.m_rowCount == 3)
    {
        if (b.m_columnCount == 1 && b.m_rowCount == 3)
        {
            Matrix c = Matrix(3, 1);
            c = Matrix::addMatrix(a, b);

            return c;
        }

        throw std::runtime_error("The second argument isn't a Vec3.");
    }

    throw std::runtime_error("The first argument isn't a Vec3.");
}

Matrix Matrix::rotationX(double alpha, const Matrix& a)
{
    if (a.m_columnCount == 1 && a.m_rowCount == 3)
    {
        Matrix rotaMatX = Matrix(3, 3);

        rotaMatX.m_matrix[0][0] = 1;
        rotaMatX.m_matrix[0][1] = 0;
        rotaMatX.m_matrix[0][2] = 0;

        rotaMatX.m_matrix[1][0] = 0;
        rotaMatX.m_matrix[1][1] = std::cos(alpha);
        rotaMatX.m_matrix[1][2] = -std::sin(alpha);

        rotaMatX.m_matrix[2][0] = 0;
        rotaMatX.m_matrix[2][1] = std::sin(alpha);
        rotaMatX.m_matrix[2][2] = std::cos(alpha);

        Matrix res = rotaMatX * a;

        return res;
    }

    if (a.m_columnCount == 3 && a.m_rowCount == 1)
    {
        Matrix rotaMatX = Matrix(3, 3);

        rotaMatX.m_matrix[0][0] = 1;
        rotaMatX.m_matrix[0][1] = 0;
        rotaMatX.m_matrix[0][2] = 0;

        rotaMatX.m_matrix[1][0] = 0;
        rotaMatX.m_matrix[1][1] = std::cos(alpha);
        rotaMatX.m_matrix[1][2] = -std::sin(alpha);

        rotaMatX.m_matrix[2][0] = 0;
        rotaMatX.m_matrix[2][1] = std::sin(alpha);
        rotaMatX.m_matrix[2][2] = std::cos(alpha);

        auto transposedA = Matrix::transposed(a);
        Matrix res = rotaMatX * transposedA;

        return res.transpose();
    }

    throw std::runtime_error("The matrix must be a Vec3.");
}

Matrix Matrix::rotationY(double alpha, const Matrix& a)
{
    if (a.m_columnCount == 1 && a.m_rowCount == 3)
    {
        Matrix rotaMatY = Matrix(3, 3);

        rotaMatY.m_matrix[0][0] = std::cos(alpha);
        rotaMatY.m_matrix[0][1] = 0;
        rotaMatY.m_matrix[0][2] = std::sin(alpha);

        rotaMatY.m_matrix[1][0] = 0;
        rotaMatY.m_matrix[1][1] = 1;
        rotaMatY.m_matrix[1][2] = 0;

        rotaMatY.m_matrix[2][0] = -std::sin(alpha);
        rotaMatY.m_matrix[2][1] = 0;
        rotaMatY.m_matrix[2][2] = std::cos(alpha);

        Matrix res = matrixProduct(rotaMatY, a);

        return res;
    }

    if (a.m_columnCount == 3 && a.m_rowCount == 1)
    {
        Matrix rotaMatY = Matrix(3, 3);

        rotaMatY.m_matrix[0][0] = std::cos(alpha);
        rotaMatY.m_matrix[0][1] = 0;
        rotaMatY.m_matrix[0][2] = std::sin(alpha);

        rotaMatY.m_matrix[1][0] = 0;
        rotaMatY.m_matrix[1][1] = 1;
        rotaMatY.m_matrix[1][2] = 0;

        rotaMatY.m_matrix[2][0] = -std::sin(alpha);
        rotaMatY.m_matrix[2][1] = 0;
        rotaMatY.m_matrix[2][2] = std::cos(alpha);

        auto transposedA = Matrix::transposed(a);
        Matrix res = rotaMatY * transposedA;

        return res.transpose();
    }

    throw std::runtime_error("The matrix must be a Vec3.");
}

Matrix Matrix::rotationZ(double alpha, const Matrix& a)
{
    if (a.m_columnCount == 1 && a.m_rowCount == 3)
    {
        Matrix rotaMatZ = Matrix(3, 3);

        rotaMatZ.m_matrix[0][0] = std::cos(alpha);
        rotaMatZ.m_matrix[0][1] = -std::sin(alpha);
        rotaMatZ.m_matrix[0][2] = 0;

        rotaMatZ.m_matrix[1][0] = std::sin(alpha);
        rotaMatZ.m_matrix[1][1] = std::cos(alpha);
        rotaMatZ.m_matrix[1][2] = 0;

        rotaMatZ.m_matrix[2][0] = 0;
        rotaMatZ.m_matrix[2][1] = 0;
        rotaMatZ.m_matrix[2][2] = 1;

        Matrix res = matrixProduct(rotaMatZ, a);

        return res;
    }

    if (a.m_columnCount == 3 && a.m_rowCount == 1)
    {
        Matrix rotaMatZ = Matrix(3, 3);

        rotaMatZ.m_matrix[0][0] = std::cos(alpha);
        rotaMatZ.m_matrix[0][1] = -std::sin(alpha);
        rotaMatZ.m_matrix[0][2] = 0;

        rotaMatZ.m_matrix[1][0] = std::sin(alpha);
        rotaMatZ.m_matrix[1][1] = std::cos(alpha);
        rotaMatZ.m_matrix[1][2] = 0;

        rotaMatZ.m_matrix[2][0] = 0;
        rotaMatZ.m_matrix[2][1] = 0;
        rotaMatZ.m_matrix[2][2] = 1;

        auto transposedA = Matrix::transposed(a);
        Matrix res = rotaMatZ * transposedA;

        return res.transpose();
    }

    throw std::runtime_error("The matrix must be a Vec3.");
}

Matrix Matrix::scale(double x, double y, double z, const Matrix& a)
{
    if (a.m_columnCount == 1 && a.m_rowCount == 3)
    {
        Matrix scale = Matrix(3, 3);

        scale.m_matrix[0][0] = x;
        scale.m_matrix[1][1] = y;
        scale.m_matrix[2][2] = z;

        scale.print();

        Matrix res = matrixProduct(scale, a);

        return res;
    }

    if (a.m_columnCount == 3 && a.m_rowCount == 1)
    {
        Matrix scale = Matrix(3, 3);

        scale.m_matrix[0][0] = x;
        scale.m_matrix[1][1] = y;
        scale.m_matrix[2][2] = z;

        scale.print();

        auto transposedA = Matrix::transposed(a);
        Matrix res = scale * transposedA;

        return res.transpose();
    }

    throw std::runtime_error("The matrix must be a Vec3.");
}

Matrix Matrix::transposed(const Matrix& a)
{
    if (a.m_columnCount != 0 || a.m_rowCount != 0)
    {
        Matrix res = Matrix(a.m_columnCount, a.m_rowCount);

        for (std::size_t i = 0; i < a.m_rowCount; i++)
        {
            for (std::size_t j = 0; j < a.m_columnCount; j++)
            {
                res.m_matrix[j][i] = a.m_matrix[i][j];
            }
        }

        return res;
    }

    throw std::runtime_error("The m_matrix isn't init.");
}

double Matrix::getNorm(const Matrix& a)
{
    if (a.m_columnCount == 1 && a.m_rowCount == 3)
    {
        double x = a.m_matrix[0][0];
        double y = a.m_matrix[1][0];
        double z = a.m_matrix[2][0];

        double norm = std::sqrt(std::pow(x, 2) + std::pow(y, 2) + std::pow(z, 2));

        return norm;
    }

    if (a.m_columnCount == 3 && a.m_rowCount == 1)
    {
        double x = a.m_matrix[0][0];
        double y = a.m_matrix[0][1];
        double z = a.m_matrix[0][2];

        double norm = std::sqrt(std::pow(x, 2) + std::pow(y, 2) + std::pow(z, 2));

        return norm;
    }

    throw std::runtime_error("The matrix must be a Vec3.");
}

Matrix Matrix::normalize(const Matrix& a)
{
    if (a.m_columnCount == 1 && a.m_rowCount == 3)
    {
        double norm = Matrix::getNorm(a);

        double x = a.m_matrix[0][0] / norm;
        double y = a.m_matrix[1][0] / norm;
        double z = a.m_matrix[2][0] / norm;

        a.m_matrix[0][0] = x;
        a.m_matrix[1][0] = y;
        a.m_matrix[2][0] = z;

        return a;
    }

    if (a.m_columnCount == 3 && a.m_rowCount == 1)
    {
        double norm = Matrix::getNorm(a);

        double x = a.m_matrix[0][0] / norm;
        double y = a.m_matrix[0][1] / norm;
        double z = a.m_matrix[0][2] / norm;

        a.m_matrix[0][0] = x;
        a.m_matrix[0][1] = y;
        a.m_matrix[0][2] = z;

        return a;
    }

    throw std::runtime_error("The matrix must be a Vec3.");
}

Matrix Matrix::invert(const Matrix& a)
{
    if (a.m_columnCount != 3 && a.m_rowCount != 3)
    {
        throw std::runtime_error("the m_matrix is not a 3*3 matrix");
    }

    double matrixDet = Matrix::determinant(a);

    if (matrixDet == 0)
    {
        throw std::runtime_error("the m_matrix is not invertible");
    }

    // Create submatrix to have the determinant
    Matrix subMat00(2, 2, {{a.m_matrix[1][1], a.m_matrix[1][2]}, {a.m_matrix[2][1], a.m_matrix[2][2]}});
    Matrix subMat01(2, 2, {{a.m_matrix[1][0], a.m_matrix[1][2]}, {a.m_matrix[2][0], a.m_matrix[2][2]}});
    Matrix subMat02(2, 2, {{a.m_matrix[1][0], a.m_matrix[1][1]}, {a.m_matrix[2][0], a.m_matrix[2][1]}});

    Matrix subMat10(2, 2, {{a.m_matrix[0][1], a.m_matrix[0][2]}, {a.m_matrix[2][1], a.m_matrix[2][2]}});
    Matrix subMat11(2, 2, {{a.m_matrix[0][0], a.m_matrix[0][2]}, {a.m_matrix[2][0], a.m_matrix[2][2]}});
    Matrix subMat12(2, 2, {{a.m_matrix[0][0], a.m_matrix[0][1]}, {a.m_matrix[2][0], a.m_matrix[2][1]}});

    Matrix subMat20(2, 2, {{a.m_matrix[0][1], a.m_matrix[0][2]}, {a.m_matrix[1][1], a.m_matrix[1][2]}});
    Matrix subMat21(2, 2, {{a.m_matrix[0][0], a.m_matrix[0][2]}, {a.m_matrix[1][0], a.m_matrix[1][2]}});
    Matrix subMat22(2, 2, {{a.m_matrix[0][0], a.m_matrix[0][1]}, {a.m_matrix[1][0], a.m_matrix[1][1]}});

    // Get the determinant for each submatrix
    double det00 = Matrix::determinant(subMat00);
    double det01 = -Matrix::determinant(subMat01);
    double det02 = Matrix::determinant(subMat02);

    double det10 = -Matrix::determinant(subMat10);
    double det11 = Matrix::determinant(subMat11);
    double det12 = -Matrix::determinant(subMat12);

    double det20 = Matrix::determinant(subMat20);
    double det21 = -Matrix::determinant(subMat21);
    double det22 = Matrix::determinant(subMat22);

    Matrix toTranspose(3, 3, {{det00, det01, det02}, {det10, det11, det12}, {det20, det21, det22}});

    Matrix transposed = Matrix::transposed(toTranspose);

    double scalar = 1 / matrixDet;

    Matrix invert = Matrix::scalarProduct(transposed, scalar);

    return invert;
}

double Matrix::determinant(const Matrix& a)
{
    // 3*3 matrix
    if (a.m_columnCount == 3 && a.m_rowCount == 3)
    {
        double det = a.m_matrix[0][0] * a.m_matrix[1][1] * a.m_matrix[2][2];
        det -= a.m_matrix[2][0] * a.m_matrix[1][1] * a.m_matrix[0][2];
        det += a.m_matrix[0][1] * a.m_matrix[1][2] * a.m_matrix[2][0];
        det -= a.m_matrix[2][1] * a.m_matrix[1][2] * a.m_matrix[0][0];
        det += a.m_matrix[0][2] * a.m_matrix[1][0] * a.m_matrix[2][1];
        det -= a.m_matrix[2][2] * a.m_matrix[1][0] * a.m_matrix[0][1];

        return det;
    }
    // 2*2 matrix
    if (a.m_columnCount == 2 && a.m_rowCount == 2)
    {
        double det = a.m_matrix[0][0] * a.m_matrix[1][1] - (a.m_matrix[0][1] * a.m_matrix[1][0]);

        return det;
    }

    throw std::runtime_error("the m_matrix is not a 3*3 matrix");
}

Matrix Matrix::reflection(const Matrix& originPrimary,
                          const Matrix& directionPrimary,
                          const Matrix& intersectionPoint,
                          const Matrix& intersectionNormal)
{
    //TODO

    throw std::runtime_error("Not implemented.");

    return Matrix(1, 1);
}

void Matrix::allocate(std::size_t rowCount, std::size_t columnCount)
{
    if (m_matrix != nullptr && m_rowCount == rowCount && m_columnCount == columnCount)
        return;

    deallocate();

    m_rowCount = rowCount;
    m_columnCount = columnCount;

    m_matrix = new double*[m_rowCount];

    for (std::size_t i = 0; i < m_rowCount; i++)
    {
        m_matrix[i] = new double[m_columnCount];
    }
}

void Matrix::deallocate()
{
    if (m_matrix != nullptr)
    {
        for (std::size_t i = 0; i < m_rowCount; i++)
        {
            delete[] m_matrix[i];
        }

        delete[] m_matrix;

        m_matrix = nullptr;
    }
}

void Matrix::fill(const std::initializer_list<std::initializer_list<double>>& initializerList)
{
    std::size_t line = 0;
    std::size_t column = 0;
    for (const auto& list : initializerList)
    {
        if (line >= m_rowCount)
            throw std::runtime_error("Wrong initializer list.");

        for (const auto& value : list)
        {
            if (column >= m_columnCount)
                throw std::runtime_error("Wrong initializer list.");

            m_matrix[line][column] = value;
            column++;
        }

        line++;
        column = 0;
    }
}

void Matrix::fill(const Matrix& a)
{
    for (std::size_t i = 0; i < m_rowCount; i++)
    {
        for (std::size_t j = 0; j < m_columnCount; j++)
        {
            m_matrix[i][j] = a.m_matrix[i][j];
        }
    }
}

void Matrix::fill(double value)
{
    for (std::size_t i = 0; i < m_rowCount; i++)
    {
        for (std::size_t j = 0; j < m_columnCount; j++)
        {
            m_matrix[i][j] = 0;
        }
    }
}