#include "Matrix.h"

#include "Math.h"
#include "Utils.h"
#include "Vector3.h"

#include <algorithm>
#include <cstring>

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

Matrix::Matrix(const Matrix& matrix) : m_rowCount(matrix.m_rowCount), m_columnCount(matrix.m_columnCount)
{
    allocate(m_rowCount, m_columnCount);
    fill(matrix);
}

Matrix::Matrix(Matrix&& matrix) noexcept
{
    MOVE(matrix);
}

Matrix::~Matrix()
{
    deallocate();
}

void Matrix::create(std::size_t rowCount, std::size_t columnCount)
{
    allocate(rowCount, columnCount);
}

void Matrix::print(const std::string& name) const
{
    if (m_columnCount == 0 || m_rowCount == 0)
    {
        throw Exception::Matrix::NotInitialized();
    }

    if (!name.empty())
        std::cout << "Matrix '" << name << "' print:" << std::endl;
    else
        std::cout << "Matrix print:" << std::endl;

    for (std::size_t i = 0; i < m_rowCount; i++)
    {
        std::cout << "[ ";
        for (std::size_t j = 0; j < m_columnCount; j++)
        {
            std::cout << matrix(i, j) << " ";
        }
        std::cout << "]" << std::endl;
    }
}

void Matrix::setValue(std::size_t row, std::size_t column, double value)
{
    if (m_matrix == nullptr)
        throw Exception::Matrix::NotInitialized();

    if (row >= m_rowCount || column >= m_columnCount)
        throw Exception::Matrix::WrongCoordinates("Can't set value.");

    matrix(row, column) = value;
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
        throw Exception::Matrix::NotVector3("Can't cast to Vector3.");

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

double Matrix::scalarProduct(const Matrix& b) const
{
    return Matrix::scalarProduct(*this, b);
}

Matrix& Matrix::round()
{
    *this = Matrix::round(*this);
    return *this;
}

Matrix& Matrix::vectProd(const Matrix& a)
{
    *this = Matrix::vectProduct(*this, a);
    return *this;
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

Matrix& Matrix::operator=(Matrix&& matrix) noexcept
{
    MOVE(matrix);

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
            if (!areDoubleEqual(matrix.matrix(row, column), this->matrix(row, column)))
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
        throw Exception::Matrix::NotSameSize("Can't add matrices.");
    }

    Matrix c = Matrix(a.m_rowCount, a.m_columnCount);

    for (std::size_t i = 0; i < c.m_rowCount; i++)
    {
        for (std::size_t j = 0; j < c.m_columnCount; j++)
        {
            c.matrix(i, j) = a.matrix(i, j) + b.matrix(i, j);
        }
    }

    return c;
}

Matrix Matrix::subMatrix(const Matrix& a, const Matrix& b)
{
    if ((a.m_columnCount != b.m_columnCount) || (a.m_rowCount != b.m_rowCount))
    {
        throw Exception::Matrix::NotSameSize("Can't subtract matrices.");
    }

    Matrix c = Matrix(a.m_rowCount, a.m_columnCount);

    for (std::size_t i = 0; i < c.m_rowCount; i++)
    {
        for (std::size_t j = 0; j < c.m_columnCount; j++)
        {
            c.matrix(i, j) = a.matrix(i, j) - b.matrix(i, j);
        }
    }

    return c;
}

Matrix Matrix::scalarProduct(const Matrix& a, double scalar)
{
    if (a.m_columnCount == 0 || a.m_rowCount == 0)
    {
        throw Exception::Matrix::NotInitialized();
    }

    Matrix c = Matrix(a.m_rowCount, a.m_columnCount);

    for (std::size_t i = 0; i < c.m_rowCount; i++)
    {
        for (std::size_t j = 0; j < c.m_columnCount; j++)
        {
            c.matrix(i, j) = a.matrix(i, j) * scalar;
        }
    }

    return c;
}

Matrix Matrix::matrixProduct(const Matrix& a, const Matrix& b)
{
    if (a.m_columnCount == 0 || a.m_columnCount != b.m_rowCount)
    {
        throw Exception::Matrix::WrongSizesForProduct();
    }

    Matrix c = Matrix(a.m_rowCount, b.m_columnCount);

    for (std::size_t i = 0; i < a.m_rowCount; i++)
    {
        for (std::size_t j = 0; j < b.m_columnCount; j++)
        {
            for (std::size_t k = 0; k < b.m_rowCount; k++)
            {
                c.matrix(i, j) = a.matrix(i, k) * b.matrix(k, j) + c.matrix(i, j);
            }
        }
    }

    return c;
}

Matrix Matrix::translation(const Matrix& a, const Matrix& b)
{
    if (a.m_columnCount != b.getColumnCount() && a.m_rowCount != b.m_rowCount)
    {
        throw Exception::Matrix::NotSameSize("For translation.");
    }

    Matrix c = Matrix::addMatrix(a, b);

    return c;
}

Matrix Matrix::rotationX(double alpha, const Matrix& a)
{
    if (a.m_columnCount == 1 && a.m_rowCount == 3)
    {
        Matrix rotaMatX = Matrix(3, 3);

        rotaMatX.matrix(0, 0) = 1;
        rotaMatX.matrix(0, 1) = 0;
        rotaMatX.matrix(0, 2) = 0;

        rotaMatX.matrix(1, 0) = 0;
        rotaMatX.matrix(1, 1) = std::cos(alpha);
        rotaMatX.matrix(1, 2) = -std::sin(alpha);

        rotaMatX.matrix(2, 0) = 0;
        rotaMatX.matrix(2, 1) = std::sin(alpha);
        rotaMatX.matrix(2, 2) = std::cos(alpha);

        Matrix res = rotaMatX * a;

        return res;
    }

    if (a.m_columnCount == 3 && a.m_rowCount == 1)
    {
        Matrix rotaMatX = Matrix(3, 3);

        rotaMatX.matrix(0, 0) = 1;
        rotaMatX.matrix(0, 1) = 0;
        rotaMatX.matrix(0, 2) = 0;

        rotaMatX.matrix(1, 0) = 0;
        rotaMatX.matrix(1, 1) = std::cos(alpha);
        rotaMatX.matrix(1, 2) = -std::sin(alpha);

        rotaMatX.matrix(2, 0) = 0;
        rotaMatX.matrix(2, 1) = std::sin(alpha);
        rotaMatX.matrix(2, 2) = std::cos(alpha);

        auto transposedA = Matrix::transposed(a);
        Matrix res = rotaMatX * transposedA;

        return res.transpose();
    }

    throw Exception::Matrix::NotVector3("Need to have a Vector3 ((3,1) or (1,3)) to do a rotation.");
}

Matrix Matrix::rotationY(double alpha, const Matrix& a)
{
    if (a.m_columnCount == 1 && a.m_rowCount == 3)
    {
        Matrix rotaMatY = Matrix(3, 3);

        rotaMatY.matrix(0, 0) = std::cos(alpha);
        rotaMatY.matrix(0, 1) = 0;
        rotaMatY.matrix(0, 2) = std::sin(alpha);

        rotaMatY.matrix(1, 0) = 0;
        rotaMatY.matrix(1, 1) = 1;
        rotaMatY.matrix(1, 2) = 0;

        rotaMatY.matrix(2, 0) = -std::sin(alpha);
        rotaMatY.matrix(2, 1) = 0;
        rotaMatY.matrix(2, 2) = std::cos(alpha);

        Matrix res = matrixProduct(rotaMatY, a);

        return res;
    }

    if (a.m_columnCount == 3 && a.m_rowCount == 1)
    {
        Matrix rotaMatY = Matrix(3, 3);

        rotaMatY.matrix(0, 0) = std::cos(alpha);
        rotaMatY.matrix(0, 1) = 0;
        rotaMatY.matrix(0, 2) = std::sin(alpha);

        rotaMatY.matrix(1, 0) = 0;
        rotaMatY.matrix(1, 1) = 1;
        rotaMatY.matrix(1, 2) = 0;

        rotaMatY.matrix(2, 0) = -std::sin(alpha);
        rotaMatY.matrix(2, 1) = 0;
        rotaMatY.matrix(2, 2) = std::cos(alpha);

        auto transposedA = Matrix::transposed(a);
        Matrix res = rotaMatY * transposedA;

        return res.transpose();
    }

    throw Exception::Matrix::NotVector3("Need to have a Vector3 ((3,1) or (1,3)) to do a rotation.");
}

Matrix Matrix::rotationZ(double alpha, const Matrix& a)
{
    if (a.m_columnCount == 1 && a.m_rowCount == 3)
    {
        Matrix rotaMatZ = Matrix(3, 3);

        rotaMatZ.matrix(0, 0) = std::cos(alpha);
        rotaMatZ.matrix(0, 1) = -std::sin(alpha);
        rotaMatZ.matrix(0, 2) = 0;

        rotaMatZ.matrix(1, 0) = std::sin(alpha);
        rotaMatZ.matrix(1, 1) = std::cos(alpha);
        rotaMatZ.matrix(1, 2) = 0;

        rotaMatZ.matrix(2, 0) = 0;
        rotaMatZ.matrix(2, 1) = 0;
        rotaMatZ.matrix(2, 2) = 1;

        Matrix res = matrixProduct(rotaMatZ, a);

        return res;
    }

    if (a.m_columnCount == 3 && a.m_rowCount == 1)
    {
        Matrix rotaMatZ = Matrix(3, 3);

        rotaMatZ.matrix(0, 0) = std::cos(alpha);
        rotaMatZ.matrix(0, 1) = -std::sin(alpha);
        rotaMatZ.matrix(0, 2) = 0;

        rotaMatZ.matrix(1, 0) = std::sin(alpha);
        rotaMatZ.matrix(1, 1) = std::cos(alpha);
        rotaMatZ.matrix(1, 2) = 0;

        rotaMatZ.matrix(2, 0) = 0;
        rotaMatZ.matrix(2, 1) = 0;
        rotaMatZ.matrix(2, 2) = 1;

        auto transposedA = Matrix::transposed(a);
        Matrix res = rotaMatZ * transposedA;

        return res.transpose();
    }

    throw Exception::Matrix::NotVector3("Need to have a Vector3 ((3,1) or (1,3)) to do a rotation.");
}

Matrix Matrix::scale(double x, double y, double z, const Matrix& a)
{
    if (a.m_columnCount == 1 && a.m_rowCount == 3)
    {
        Matrix scale = Matrix(3, 3);

        scale.matrix(0, 0) = x;
        scale.matrix(1, 1) = y;
        scale.matrix(2, 2) = z;

        Matrix res = matrixProduct(scale, a);

        return res;
    }

    if (a.m_columnCount == 3 && a.m_rowCount == 1)
    {
        Matrix scale = Matrix(3, 3);

        scale.matrix(0, 0) = x;
        scale.matrix(1, 1) = y;
        scale.matrix(2, 2) = z;

        auto transposedA = Matrix::transposed(a);
        Matrix res = scale * transposedA;

        return res.transpose();
    }

    throw Exception::Matrix::NotVector3("Need to have a Vector3 ((3,1) or (1,3)) to scale.");
}

Matrix Matrix::transposed(const Matrix& a)
{
    if (a.m_columnCount != 0 && a.m_rowCount != 0)
    {
        Matrix res = Matrix(a.m_columnCount, a.m_rowCount);

        for (std::size_t i = 0; i < a.m_rowCount; i++)
        {
            for (std::size_t j = 0; j < a.m_columnCount; j++)
            {
                res.matrix(j, i) = a.matrix(i, j);
            }
        }

        return res;
    }

    throw Exception::Matrix::NotInitialized("Impossible to transpose the matrix.");
}

double Matrix::getNorm(const Matrix& a)
{
    if (a.m_columnCount == 1 && a.m_rowCount == 3)
    {
        double x = a.matrix(0, 0);
        double y = a.matrix(1, 0);
        double z = a.matrix(2, 0);

        double norm = std::sqrt(pow2(x) + pow2(y) + pow2(z));

        return norm;
    }

    if (a.m_columnCount == 3 && a.m_rowCount == 1)
    {
        double x = a.matrix(0, 0);
        double y = a.matrix(0, 1);
        double z = a.matrix(0, 2);

        double norm = std::sqrt(pow2(x) + pow2(y) + pow2(z));

        return norm;
    }

    throw Exception::Matrix::NotVector3("Need to have a Vector3 ((3,1) or (1,3)) to get the norm.");
}

Matrix Matrix::normalize(const Matrix& a)
{
    if (a.m_columnCount == 1 && a.m_rowCount == 3)
    {
        double norm = Matrix::getNorm(a);

        double x = a.matrix(0, 0) / norm;
        double y = a.matrix(1, 0) / norm;
        double z = a.matrix(2, 0) / norm;

        a.matrix(0, 0) = x;
        a.matrix(1, 0) = y;
        a.matrix(2, 0) = z;

        return a;
    }

    if (a.m_columnCount == 3 && a.m_rowCount == 1)
    {
        double norm = Matrix::getNorm(a);

        double x = a.matrix(0, 0) / norm;
        double y = a.matrix(0, 1) / norm;
        double z = a.matrix(0, 2) / norm;

        a.matrix(0, 0) = x;
        a.matrix(0, 1) = y;
        a.matrix(0, 2) = z;

        return a;
    }

    throw Exception::Matrix::NotVector3("Need to have a Vector3 ((3,1) or (1,3)) to normalize.");
}

Matrix Matrix::invert(const Matrix& a)
{
    if (a.m_columnCount != 3 && a.m_rowCount != 3)
    {
        throw Exception::Matrix::WrongSize("Need to be a (3,3) matrix to invert it.");
    }

    double matrixDet = Matrix::determinant(a);

    if (matrixDet == 0)
    {
        throw Exception::Matrix::NotInvertible();
    }

    // Create submatrix to have the determinant
    Matrix subMat00(2, 2, {{a.matrix(1, 1), a.matrix(1, 2)}, {a.matrix(2, 1), a.matrix(2, 2)}});
    Matrix subMat01(2, 2, {{a.matrix(1, 0), a.matrix(1, 2)}, {a.matrix(2, 0), a.matrix(2, 2)}});
    Matrix subMat02(2, 2, {{a.matrix(1, 0), a.matrix(1, 1)}, {a.matrix(2, 0), a.matrix(2, 1)}});

    Matrix subMat10(2, 2, {{a.matrix(0, 1), a.matrix(0, 2)}, {a.matrix(2, 1), a.matrix(2, 2)}});
    Matrix subMat11(2, 2, {{a.matrix(0, 0), a.matrix(0, 2)}, {a.matrix(2, 0), a.matrix(2, 2)}});
    Matrix subMat12(2, 2, {{a.matrix(0, 0), a.matrix(0, 1)}, {a.matrix(2, 0), a.matrix(2, 1)}});

    Matrix subMat20(2, 2, {{a.matrix(0, 1), a.matrix(0, 2)}, {a.matrix(1, 1), a.matrix(1, 2)}});
    Matrix subMat21(2, 2, {{a.matrix(0, 0), a.matrix(0, 2)}, {a.matrix(1, 0), a.matrix(1, 2)}});
    Matrix subMat22(2, 2, {{a.matrix(0, 0), a.matrix(0, 1)}, {a.matrix(1, 0), a.matrix(1, 1)}});

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
        double det = a.matrix(0, 0) * a.matrix(1, 1) * a.matrix(2, 2);
        det -= a.matrix(2, 0) * a.matrix(1, 1) * a.matrix(0, 2);
        det += a.matrix(0, 1) * a.matrix(1, 2) * a.matrix(2, 0);
        det -= a.matrix(2, 1) * a.matrix(1, 2) * a.matrix(0, 0);
        det += a.matrix(0, 2) * a.matrix(1, 0) * a.matrix(2, 1);
        det -= a.matrix(2, 2) * a.matrix(1, 0) * a.matrix(0, 1);

        return det;
    }
    // 2*2 matrix
    if (a.m_columnCount == 2 && a.m_rowCount == 2)
    {
        double det = a.matrix(0, 0) * a.matrix(1, 1) - (a.matrix(0, 1) * a.matrix(1, 0));

        return det;
    }

    throw Exception::Matrix::WrongSize("Need to be a (3,3) matrix to get the determinant.");
}

double Matrix::scalarProduct(const Matrix& a, const Matrix& b)
{
    if (a.m_columnCount != b.getColumnCount() && a.m_rowCount != b.m_rowCount)
    {
        throw Exception::Matrix::NotSameSize("For the scalar product.");
    }

    if (a.m_columnCount == 1 && a.m_rowCount == 3)
    {

        double value = 0;
        for (size_t i = 0; i < a.m_rowCount; i++)
        {
            value += a.matrix(i, 0) * b.matrix(i, 0);
        }

        return value;
    }

    if (a.m_columnCount == 3 && a.m_rowCount == 1)
    {
        double value = 0;
        for (size_t i = 0; i < a.m_columnCount; i++)
        {
            value += a.matrix(0, i) * b.matrix(0, i);
        }

        return value;
    }

    throw Exception::Matrix::NotVector3("For the scalar product.");
}

Matrix Matrix::reflection(const Matrix& directionPrimary, const Matrix& intersectionNormal)
{
    if ((directionPrimary.m_rowCount != 3 && directionPrimary.m_rowCount != 1) ||
        (intersectionNormal.m_rowCount != 3 && intersectionNormal.m_rowCount != 1))
    {
        throw Exception::Matrix::WrongSize("Must be (1,3) to calculate the reflection.");
    }

    // normalize the 2 vectors
    Matrix incident = Matrix::normalize(directionPrimary);
    Matrix normal = Matrix::normalize(intersectionNormal);

    // calculate the reflected vector : I - 2 * (I.N)*N
    double scalarProd = incident.scalarProduct(normal);
    scalarProd *= 2;
    normal *= scalarProd;

    Matrix reflectedDir = Matrix::subMatrix(incident, normal);

    return reflectedDir;
}

Matrix Matrix::round(const Matrix& matrix)
{
    Matrix res = matrix;
    for (std::size_t i = 0; i < res.m_rowCount; i++)
    {
        for (std::size_t j = 0; j < res.m_columnCount; j++)
        {
            res.matrix(i, j) = std::round(res.matrix(i, j));
        }
    }

    return res;
}

bool Matrix::areApproximatelyEqual(const Matrix& a, const Matrix& b, double precision)
{
    if (a.getRowCount() != b.getRowCount() || a.getColumnCount() != b.getColumnCount())
        return false;

    for (std::size_t row = 0; row < a.getRowCount(); row++)
    {
        for (std::size_t column = 0; column < a.getColumnCount(); column++)
        {
            if (!areDoubleApproximatelyEqual(a.value(row, column), b.value(row, column), precision))
                return false;
        }
    }

    return true;
}

Matrix Matrix::vectProduct(const Matrix& a, const Matrix& b)
{
    if (a.getRowCount() != 1 && a.getColumnCount() != 3 && b.getRowCount() != 1 && b.getColumnCount() != 3)
    {
        throw Exception::Matrix::WrongSize("The 2 matrix must be a Vec3 (1,3).");
    }

    double xValue = a.matrix(0, 1) * b.matrix(0, 2) - a.matrix(0, 2) * b.matrix(0, 1);
    double yValue = -a.matrix(0, 0) * b.matrix(0, 2) + a.matrix(0, 2) * b.matrix(0, 0);
    double zValue = a.matrix(0, 0) * b.matrix(0, 1) - a.matrix(0, 1) * b.matrix(0, 0);

    Matrix res(a.getRowCount(), a.getColumnCount(), {{xValue, yValue, zValue}});

    return res;
}

void Matrix::allocate(std::size_t rowCount, std::size_t columnCount)
{
    if (m_matrix != nullptr && m_rowCount == rowCount && m_columnCount == columnCount)
        return;

    deallocate();

    m_rowCount = rowCount;
    m_columnCount = columnCount;

    m_matrix = new double[m_rowCount * m_columnCount];
}

void Matrix::fill(const std::initializer_list<std::initializer_list<double>>& initializerList)
{
    std::size_t line = 0;
    std::size_t column = 0;
    for (const auto& list : initializerList)
    {
        if (line >= m_rowCount)
            throw Exception::Matrix::WrongInitializerList();

        for (const auto& value : list)
        {
            if (column >= m_columnCount)
                throw Exception::Matrix::WrongInitializerList();

            matrix(line, column) = value;
            column++;
        }

        line++;
        column = 0;
    }
}

void Matrix::fill(const Matrix& a)
{
    std::memcpy(m_matrix, a.m_matrix, m_rowCount * m_columnCount * sizeof(double));
}

void Matrix::fill(double value)
{
    std::fill(&m_matrix[0], &m_matrix[0] + m_rowCount * m_columnCount, value);
}