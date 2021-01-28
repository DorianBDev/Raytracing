#ifndef H_RAYTRACING_MATRIX_H
#define H_RAYTRACING_MATRIX_H

#include <initializer_list>
#include <iostream>
#include <stdexcept>

/**
 * @class Matrix
 * @brief Class that manage matrix calculations.
 *
 * Class that manage matrix calculations.
 * Addition, Subtraction, product with scalar, product with matrix and more.
 *
 */
class Matrix
{
public:
    /**
     * @brief Basic constructor with line and column.
     *
     * This is a basic constructor for a matrix. All the values are set to 0.
     *
     * @param nbLine
     *     Number of line for the matrix.
     *
     * @param nbCol
     *      Number of column for the matrix.
     */
    Matrix(std::size_t nbLine, std::size_t nbCol);

    /**
     * @brief Another constructor with line and column and value init.
     *
     * This is another constructor for a matrix. We also use a initializer_list to init the values of the matrix's element.
     *
     * @param nbLine
     *     Number of line for the matrix.
     *
     * @param nbLine
     *      Number of column for the matrix.
     *
     * @param initializerList
     *      List to init the values os the matrix.
     */
    Matrix(std::size_t nbLine,
           std::size_t nbCol,
           const std::initializer_list<std::initializer_list<double>>& initializerList);

    /**
     * @brief Constructor by copy.
     *
     */
    Matrix(const Matrix& /*A*/);

    /**
     * @brief Destructor of our class.
     *
     * Free the memory.
     *
     */
    ~Matrix();

    /**
     * @brief Set the values of the matrix manually.
     *
     * Update the values of the matrix with a terminal.
     *
     */
    void setvalue();

    /**
     * @brief Print a matrix.
     *
     *
     */
    void printMatrix();

    /**
     * @brief Addition of two matrix.
     *
     * The matrix must have the same dimensions.
     *
     * @param a
     *     One matrix.
     *
     * @param b
     *      A second matrix.
     *
     * @return
     *      Return the result of the addition of matrix a and b.
     */
    static Matrix addMat(Matrix& a, Matrix& b);

    /**
     * @brief Subtraction of two matrix.
     *
     * The matrix must have the same dimensions.
     *
     * @param a
     *     One matrix.
     *
     * @param b
     *      A second matrix.
     *
     * @return
     *      Return the result of the subtraction of matrix a and b (a-b).
     */
    static Matrix subMat(Matrix& a, Matrix& b);

    /**
      * @brief Multiplication with a scalar.
      *
      * Multiply all the values with a scalar.
      *
      * @param a
      *     One matrix.
      *
      * @param scalar
      *      A scalar the we want to multiply the matrix with.
      *
      * @return
      *      Return the result of the multiplication of the matrix and the scalar.
     */
    static Matrix scalMult(Matrix& a, double scalar);

    /**
      * @brief Multiplication two matrix.
      *
      * Multiply two matrix. Verify that they have the necessary dimension to permit this action.
      *
      *
      * @param a
      *     One matrix.
      *
      * @param b
      *      Second matrix.
      *
      * @return
      *      Return the result of the multiplication of the two matrix.
      *      Be safe of the order : a*b.
     */
    static Matrix prodMat(Matrix& a, Matrix& b);

    /**
      * @brief Translation of one 3D vector.
      *
      * Translate a 3D vector with another 3D vector.
      * Be careful, this only works with 3D vector.
      *
      * @see addMat
      *
      * @param a
      *     One 3D vector.
      *
      * @param b
      *      3D vector which represent the direction.
      *
      * @return
      *      Return a nex 3D vector resulting of the translation of the vector a by the direction b.
      *      The operation is the following : a+b.
     */
    static Matrix translation(Matrix& a, Matrix& b);

    /**
      * @brief Rotation on x axis.
      *
      * Rotate a 3D vector on the x axis.
      * Be careful, this only works with 3D vector.
      * The rotation matrix is 3*3 matrix.
      *
      * @see prodMat
      *
      * @param alpha
      *     The angle of the rotation.
      *
      * @param a
      *      3D vector to rotate. Must be a 3D vector
      *
      * @return
      *      Return a new 3D vector resulting of the rotation of the vector on the x axis.
     */
    static Matrix rotationX(double alpha, Matrix& a);

    /**
      * @brief Rotation on y axis.
      *
      * Rotate a 3D vector on the y axis.
      * Be careful, this only works with 3D vector.
      * The rotation matrix is 3*3 matrix.
      * There is a dependency with the prodMat method.
      *
      *
      * @param alpha
      *     The angle of the rotation.
      *
      * @param a
      *      3D vector to rotate. Must be a 3D vector
      *
      * @return
      *      Return a new 3D vector resulting of the rotation of the vector on the y axis.
     */
    static Matrix rotationY(double alpha, Matrix& a);

    /**
      * @brief Rotation on z axis.
      *
      * Rotate a 3D vector on the z axis.
      * Be careful, this only works with 3D vector.
      * The rotation matrix is 3*3 matrix.
      * There is a dependency with the prodMat method.
      *
      *
      * @param alpha
      *     The angle of the rotation.
      *
      * @param a
      *      3D vector to rotate. Must be a 3D vector
      *
      * @return
      *      Return a new 3D vector resulting of the rotation of the vector on the z axis.
      */
    static Matrix rotationZ(double alpha, Matrix& a);

    /**
      * @brief Scale a 3D vector.
      *
      * Be careful, this only works with 3D vector.
      * The scaling matrix is 3*3 matrix.
      *
      * @see prodMat
      *
      * @param x
      *     The coefficient for the x component of the 3D vector.
      *
      * @param y
      *      The coefficient for the y component of the 3D vector.
      *
      * @param z
      *      The coefficient for the z component of the 3D vector.
      *
      *  @param a
      *      The 3D vector.
      *
      * @return
      *      Return a new 3D vector resulting of the scaling depending of the coefficient.
     */
    static Matrix scale(double x, double y, double z, Matrix& a);

    /**
      * @brief Transposition of a matrix.
      *
      *
      * @param a
      *     The matrix that we want to transpose.
      *
      * @return
      *      Return a new matrix which is the transpose of the matrix in parameter.
     */
    static Matrix transposed(Matrix& a);

    /**
      * @brief Get the norm of a 3D vector.
      *
      * Be careful, this only works with 3D vector.
      *
      * @param a
      *     The 3D vector.
      *
      * @return
      *      Return the norm of the 3D vector in parameter.
     */
    static double getNorm(Matrix& a);

    /**
      * @brief Normalize a 3D vector.
      *
      * Be careful, this only works with 3D vector.
      *
      * @see getNorm
      *
      * @param a
      *     The 3D vector.
      *
      * @return
      *      Return a new 3D vector which is the normalized vector of a.
     */
    static Matrix normalize(Matrix& a);

    /**
      * @brief Get the value of one item in the matrix.
      *
      * @param line
      *     The line's location of our element.
      *
      * @param column
      *     The column's location of our element.
      *
      * @return
      *      Return the value of the element at the given line and column.
     */
    double getValue(std::size_t line, std::size_t column);


private:
    /**
     * The number of the line of our matrix.
     */
    std::size_t m_dimL = 0;

    /**
     * The number of the column of our matrix.
     */
    std::size_t m_dimC = 0;

    /**
     * Store the element of our matrix.
     */
    double** m_matrix = nullptr;
};

#endif //H_RAYTRACING_MATRIX_H
