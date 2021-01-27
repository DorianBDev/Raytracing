#include "Matrix.h"

Matrix::Matrix(std::size_t nbLine, std::size_t nbCol)
{
    m_dimL = nbLine;
    m_dimC = nbCol;

    m_matrix = new double*[m_dimL];

    for (std::size_t i = 0; i < m_dimL; i++)
    {
        m_matrix[i] = new double[m_dimC];
    }

    for (std::size_t i = 0; i < m_dimL; i++)
    {
        for (std::size_t j = 0; j < m_dimC; j++)
        {
            m_matrix[i][j] = 0;
        }
    }
}

Matrix::Matrix(std::size_t nbLine,
               std::size_t nbCol,
               const std::initializer_list<std::initializer_list<double>>& initializerList)
{
    m_dimL = nbLine;
    m_dimC = nbCol;

    m_matrix = new double*[m_dimL];

    for (std::size_t i = 0; i < m_dimL; i++)
    {
        m_matrix[i] = new double[m_dimC];
    }

    std::size_t line = 0;
    std::size_t column = 0;
    for (const auto& list : initializerList)
    {
        if (line >= m_dimL)
            throw std::runtime_error("Wrong initializer list.");

        for (const auto& value : list)
        {
            if (column >= m_dimC)
                throw std::runtime_error("Wrong initializer list.");

            m_matrix[line][column] = value;
            column++;
        }
        line++;
        column = 0;
    }
}

Matrix::Matrix(const Matrix& a)
{
    m_dimL = a.m_dimL;
    m_dimC = a.m_dimC;

    m_matrix = new double*[m_dimL];

    for (std::size_t i = 0; i < m_dimL; i++)
    {
        m_matrix[i] = new double[m_dimC];
    }

    for (std::size_t i = 0; i < m_dimL; i++)
    {
        for (std::size_t j = 0; j < m_dimC; j++)
        {
            m_matrix[i][j] = a.m_matrix[i][j];
        }
    }
}

Matrix::~Matrix()
{
    if (m_matrix != nullptr)
    {
        for (std::size_t i = 0; i < m_dimL; i++)
        {
            delete[] m_matrix[i];
        }

        delete[] m_matrix;
    }
}

void Matrix::setvalue()
{
    if ((m_dimC == 0) || (m_dimL == 0))
    {
        throw std::runtime_error("The m_matrix is not init");
    }

    std::cout << "Enter Matrix elements" << std::endl;
    for (std::size_t i = 0; i < m_dimL; i++)
    {
        for (std::size_t j = 0; j < m_dimC; j++)
        {
            std::cout << "Value of [" << i << "][" << j << "]";
            std::cin >> m_matrix[i][j];
        }
    }
}

void Matrix::printMatrix()
{
    if (m_dimC == 0 || m_dimL == 0)
    {
        throw std::runtime_error("The m_matrix isn't init");
    }

    for (std::size_t i = 0; i < m_dimL; i++)
    {
        for (std::size_t j = 0; j < m_dimC; j++)
        {
            std::cout << m_matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

Matrix Matrix::addMat(Matrix& a, Matrix& b)
{
    if ((a.m_dimC != b.m_dimC) || (a.m_dimL != b.m_dimL))
    {
        throw std::runtime_error("The m_matrix haven't the same dimension");
    }


    Matrix c = Matrix(a.m_dimL, a.m_dimC);

    for (std::size_t i = 0; i < c.m_dimL; i++)
    {
        for (std::size_t j = 0; j < c.m_dimC; j++)
        {
            c.m_matrix[i][j] = a.m_matrix[i][j] + b.m_matrix[i][j];
        }
    }

    return c;
}

Matrix Matrix::subMat(Matrix& a, Matrix& b)
{
    if ((a.m_dimC != b.m_dimC) || (a.m_dimL != b.m_dimL))
    {
        throw std::runtime_error("The m_matrix haven't the same dimension");
    }


    Matrix c = Matrix(a.m_dimL, a.m_dimC);

    for (std::size_t i = 0; i < c.m_dimL; i++)
    {
        for (std::size_t j = 0; j < c.m_dimC; j++)
        {
            c.m_matrix[i][j] = a.m_matrix[i][j] - b.m_matrix[i][j];
        }
    }

    return c;
}

Matrix Matrix::scalMult(Matrix& a, double scalar)
{
    if (a.m_dimC == 0 || a.m_dimL == 0)
    {
        throw std::runtime_error("The m_matrix isn't init");
    }

    Matrix c = Matrix(a.m_dimL, a.m_dimC);

    for (std::size_t i = 0; i < c.m_dimL; i++)
    {
        for (std::size_t j = 0; j < c.m_dimC; j++)
        {
            c.m_matrix[i][j] = a.m_matrix[i][j] * scalar;
        }
    }

    return c;
}

Matrix Matrix::prodMat(Matrix& a, Matrix& b)
{
    if (a.m_dimC == 0 || a.m_dimC != b.m_dimL)
    {
        throw std::runtime_error("Problem with dimension to multiply the m_matrix");
    }

    Matrix c = Matrix(a.m_dimL, b.m_dimC);

    for (std::size_t i = 0; i < a.m_dimL; i++)
    {
        for (std::size_t j = 0; j < b.m_dimC; j++)
        {
            for (std::size_t k = 0; k < b.m_dimL; k++)
            {
                c.m_matrix[i][j] = a.m_matrix[i][k] * b.m_matrix[k][j] + c.m_matrix[i][j];
            }
        }
    }

    return c;
}

Matrix Matrix::translation(Matrix& a, Matrix& b)
{
    /* check if it's Vec3 */
    if (a.m_dimC == 1 && a.m_dimL == 3)
    {
        if (b.m_dimC == 1 && b.m_dimL == 3)
        {
            Matrix c = Matrix(3, 1);
            c = Matrix::addMat(a, b);

            return c;
        }


        throw std::runtime_error("the secong argument isn't a Vec3");
    }


    throw std::runtime_error("the first argument isn't a Vec3");
}

Matrix Matrix::rotationX(double alpha, Matrix& a)
{
    if (a.m_dimC == 1 && a.m_dimL == 3)
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

        Matrix res = prodMat(rotaMatX, a);

        return res;
    }


    throw std::runtime_error("the m_matrix need to be a Vec3");
}

Matrix Matrix::rotationY(double alpha, Matrix& a)
{
    if (a.m_dimC == 1 && a.m_dimL == 3)
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

        Matrix res = prodMat(rotaMatY, a);

        return res;
    }


    throw std::runtime_error("the m_matrix need to be a Vec3");
}

Matrix Matrix::rotationZ(double alpha, Matrix& a)
{
    if (a.m_dimC == 1 && a.m_dimL == 3)
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

        Matrix res = prodMat(rotaMatZ, a);

        return res;
    }


    throw std::runtime_error("the m_matrix need to be a Vec3");
}

Matrix Matrix::scale(double x, double y, double z, Matrix& a)
{
    if (a.m_dimC == 1 && a.m_dimL == 3)
    {
        Matrix scale = Matrix(3, 3);

        scale.m_matrix[0][0] = x;
        scale.m_matrix[1][1] = y;
        scale.m_matrix[2][2] = z;

        scale.printMatrix();

        Matrix res = prodMat(scale, a);

        return res;
    }


    throw std::runtime_error("the m_matrix need to be a Vec3");
}

Matrix Matrix::transposed(Matrix& a)
{
    if (a.m_dimC != 0 || a.m_dimL != 0)
    {
        Matrix res = Matrix(a.m_dimC, a.m_dimL);

        for (std::size_t i = 0; i < a.m_dimL; i++)
        {
            for (std::size_t j = 0; j < a.m_dimC; j++)
            {
                res.m_matrix[j][i] = a.m_matrix[i][j];
            }
        }

        return res;
    }


    throw std::runtime_error("the m_matrix isn't init");
}

double Matrix::getNorm(Matrix& a)
{
    if (a.m_dimC == 1 && a.m_dimL == 3)
    {
        double x = a.m_matrix[0][0];
        double y = a.m_matrix[1][0];
        double z = a.m_matrix[2][0];

        double norm = std::sqrt(std::pow(x, 2) + std::pow(y, 2) + std::pow(z, 2));

        return norm;
    }


    throw std::runtime_error("the m_matrix need to be a Vec3");
}

Matrix Matrix::normalize(Matrix& a)
{
    if (a.m_dimC == 1 && a.m_dimL == 3)
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


    throw std::runtime_error("the m_matrix need to be a Vec3");
}

double Matrix::getValue(std::size_t line, std::size_t column)
{
    if (line >= m_dimL ||column >= m_dimC)
        throw std::runtime_error("Wrong coordinates to get a value.");

    return m_matrix[line][column];
}