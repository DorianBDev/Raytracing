#ifndef H_RAYTRACING_MATRIX_H
#define H_RAYTRACING_MATRIX_H

#include <initializer_list>
#include <iostream>
#include <stdexcept>

class Vector3;

/**
 * @class Matrix
 * @brief Class that manage matrix calculations.
 *
 * Class that manage matrix calculations.
 * Addition, Subtraction, product with scalar, product with matrix and more.
 */
class Matrix
{
public:
    /**
     * @brief Basic constructor with line and column.
     *
     * This is a basic constructor for a matrix. All the values are set to 0.
     *
     * @param rowCount     Number of line for the matrix.
     * @param columnCount  Number of column for the matrix.
     */
    Matrix(std::size_t rowCount, std::size_t columnCount);

    /**
     * @brief Another constructor with line and column and value init.
     *
     * This is another constructor for a matrix. We also use a initializer_list to init the values of the matrix's
     * element.
     *
     * @param rowCount        Number of line for the matrix.
     * @param columnCount     Number of column for the matrix.
     * @param initializerList List to init the values os the matrix.
     */
    Matrix(std::size_t rowCount,
           std::size_t columnCount,
           const std::initializer_list<std::initializer_list<double>>& initializerList);
    Matrix(std::size_t rowCount,
           std::size_t columnCount,
           const std::initializer_list<std::initializer_list<double>>&& initializerList);

    /**
     * @brief Constructor by copy.
     */
    Matrix(const Matrix& /*A*/);

    /**
     * @brief Destructor of our class.
     *
     * Free the memory.
     */
    ~Matrix();

    /**
     * @brief Print a matrix.
     */
    void print() const;

    /**
     * @brief Get the value of one item in the matrix.
     *
     * @param row    The line's location of our element.
     * @param column The column's location of our element.
     *
     * @return Returns the value of the element at the given line and column.
     */
    double value(std::size_t row, std::size_t column) const;

    /**
     * @brief
     * @param row
     * @param column
     * @param value
     */
    void setValue(std::size_t row, std::size_t column, double value);

    /**
     * @brief Get the row count of the matrix.
     *
     * @return Returns the row count of the matrix.
     */
    std::size_t getRowCount() const;

    /**
     * @brief Get the column count of the matrix.
     *
     * @return Returns the column count of the matrix.
     */
    std::size_t getColumnCount() const;

    /**
     * @brief Convert the matrix to a Vector3.
     *
     * @return Returns the new Vector3 from the matrix.
     */
    Vector3 toVector3() const;

    /**
     * @brief Translate this matrix. (must be Vector3)
     *
     * Translate a 3D vector with another 3D vector.
     * Be careful, this only works with 3D vector.
     *
     * @param a Second 3D vector which represent the direction.
     *
     * @return Returns *this.
     *
     * @see addMatrix
     */
    Matrix& translate(const Matrix& a);

    /**
     * @brief Rotate on x axis. (must be Vector3)
     *
     * Rotate a 3D vector on the x axis.
     * Be careful, this only works with 3D vector.
     * The rotation matrix is 3*3 matrix.
     *
     * @param alpha The angle of the rotation.
     *
     * @return Returns *this.
     *
     * @see matrixProduct
     */
    Matrix& rotateX(double angle);

    /**
     * @brief Rotate on y axis. (must be Vector3)
     *
     * Rotate a 3D vector on the y axis.
     * Be careful, this only works with 3D vector.
     * The rotation matrix is 3*3 matrix.
     *
     * @param alpha The angle of the rotation.
     *
     * @return Returns *this.
     *
     * @see matrixProduct
     */
    Matrix& rotateY(double angle);

    /**
     * @brief Rotate on z axis. (must be Vector3)
     *
     * Rotate a 3D vector on the z axis.
     * Be careful, this only works with 3D vector.
     * The rotation matrix is 3*3 matrix.
     *
     * @param alpha The angle of the rotation.
     *
     * @return Returns *this.
     *
     * @see matrixProduct
     */
    Matrix& rotateZ(double angle);

    /**
     * @brief Scale this matrix. (must be Vector3)
     *
     * Be careful, this only works with 3D vector.
     * The scaling matrix is 3*3 matrix.
     *
     * @param x The coefficient for the x component of the 3D vector.
     * @param y The coefficient for the y component of the 3D vector.
     * @param z The coefficient for the z component of the 3D vector.
     *
     * @return Returns *this.
     *
     * @see matrixProduct
     */
    Matrix& scale(double x, double y, double z);

    /**
     * @brief Transpose this matrix.
     *
     * @return Returns *this.
     */
    Matrix& transpose();

    /**
     * @brief Get the norm of this matrix. (must be Vector3)
     *
     * Be careful, this only works with 3D vector.
     *
     * @return Returns the norm of the matrix.
     */
    double getNorm() const;

    /**
     * @brief Normalize this matrix. (must be Vector3)
     *
     * Be careful, this only works with 3D vector.
     *
     * @return Returns *this.
     *
     * @see getNorm
     */
    Matrix& normalize();

    /**
     * @brief Invert the matrix (only for a 3*3 matrix).
     *
     * @return Returns *this.
     *
     * @see transpose
     * @see determinant
     * @see scalarProduct
     */
    Matrix& invert();

    /**
     * @brief Get the determinant of the matrix (must be 3*3).
     *
     * @return Returns the determinant of the matrix.
     */
    double determinant() const;

    /**
     * @brief Get the scalar product of 2 vec3.
     *
     * @return Returns the the scalar product of 2 vec3.
     */
    double scalarProduct(const Matrix& b) const;

    /**
     * @brief Round this matrix.
     *
     * @return Returns *this.
     */
    Matrix& round();

    /////////////////////////////////////////////////////////////////////
    /// Operators
    /////////////////////////////////////////////////////////////////////

    Matrix& operator=(const Matrix& matrix);
    Matrix& operator+=(const Matrix& matrix);
    Matrix& operator-=(const Matrix& matrix);
    Matrix& operator*=(const Matrix& matrix);
    Matrix& operator*=(double scalar);
    Matrix operator+(const Matrix& matrix) const;
    Matrix operator-(const Matrix& matrix) const;
    Matrix operator*(const Matrix& matrix) const;
    Matrix operator*(double scalar) const;
    bool operator==(const Matrix& matrix) const;
    bool operator!=(const Matrix& matrix) const;

    /////////////////////////////////////////////////////////////////////
    /// Static methods
    /////////////////////////////////////////////////////////////////////

    /**
     * @brief Addition of two matrix.
     *
     * The matrix must have the same dimensions.
     *
     * @param a The first matrix.
     * @param b The second matrix.
     *
     * @return Returns the result of the addition of matrix a and b.
     */
    static Matrix addMatrix(const Matrix& a, const Matrix& b);

    /**
     * @brief Subtraction of two matrix.
     *
     * The matrix must have the same dimensions.
     *
     * @param a The first matrix.
     * @param b The second matrix.
     *
     * @return Returns the result of the subtraction of matrix a and b (a-b).
     */
    static Matrix subMatrix(const Matrix& a, const Matrix& b);

    /**
     * @brief Multiplication with a scalar.
     *
     * Multiply all the values with a scalar.
     *
     * @param a      One matrix.
     * @param scalar A scalar the we want to multiply the matrix with.
     *
     * @return Returns the result of the multiplication of the matrix and the scalar.
     */
    static Matrix scalarProduct(const Matrix& a, double scalar);

    /**
     * @brief Multiplication two matrix.
     *
     * Multiply two matrix. Verify that they have the necessary dimension to permit this action.
     *
     * @param a The first matrix.
     * @param b The second matrix.
     *
     * @return Returns the result of the multiplication of the two matrix. Be safe of the order : a*b.
     */
    static Matrix matrixProduct(const Matrix& a, const Matrix& b);

    /**
     * @brief Translation of one 3D vector.
     *
     * Translate a 3D vector with another 3D vector.
     * Be careful, this only works with 3D vector.
     *
     * @param a First 3D vector.
     * @param b Second 3D vector which represent the direction.
     *
     * @return Returns a nex 3D vector resulting of the translation of the vector a by the direction b. The operation
     *         is the following : a+b.
     *
     * @see addMatrix
     */
    static Matrix translation(const Matrix& a, const Matrix& b);

    /**
     * @brief Rotation on x axis.
     *
     * Rotate a 3D vector on the x axis.
     * Be careful, this only works with 3D vector.
     * The rotation matrix is 3*3 matrix.
     *
     * @param alpha The angle of the rotation.
     * @param a     3D vector to rotate. Must be a 3D vector
     *
     * @return Returns a new 3D vector resulting of the rotation of the vector on the x axis.
     *
     * @see matrixProduct
     */
    static Matrix rotationX(double alpha, const Matrix& a);

    /**
     * @brief Rotation on y axis.
     *
     * Rotate a 3D vector on the y axis.
     * Be careful, this only works with 3D vector.
     * The rotation matrix is 3*3 matrix.
     * There is a dependency with the matrixProduct method.
     *
     * @param alpha The angle of the rotation.
     * @param a     3D vector to rotate. Must be a 3D vector
     *
     * @return Returns a new 3D vector resulting of the rotation of the vector on the y axis.
     */
    static Matrix rotationY(double alpha, const Matrix& a);

    /**
     * @brief Rotation on z axis.
     *
     * Rotate a 3D vector on the z axis.
     * Be careful, this only works with 3D vector.
     * The rotation matrix is 3*3 matrix.
     * There is a dependency with the matrixProduct method.
     *
     * @param alpha The angle of the rotation.
     * @param a     3D vector to rotate. Must be a 3D vector
     *
     * @return Returns a new 3D vector resulting of the rotation of the vector on the z axis.
     */
    static Matrix rotationZ(double alpha, const Matrix& a);

    /**
     * @brief Scale a 3D vector.
     *
     * Be careful, this only works with 3D vector.
     * The scaling matrix is 3*3 matrix.
     *
     * @param x The coefficient for the x component of the 3D vector.
     * @param y The coefficient for the y component of the 3D vector.
     * @param z The coefficient for the z component of the 3D vector.
     * @param a The 3D vector.
     *
     * @return Returns a new 3D vector resulting of the scaling depending of the coefficient.
     *
     * @see matrixProduct
     */
    static Matrix scale(double x, double y, double z, const Matrix& a);

    /**
     * @brief Transposition of a matrix.
     *
     * @param a The matrix that we want to transpose.
     *
     * @return Returns a new matrix which is the transpose of the matrix in parameter.
     */
    static Matrix transposed(const Matrix& a);

    /**
     * @brief Get the norm of a 3D vector.
     *
     * Be careful, this only works with 3D vector.
     *
     * @param a The 3D vector.
     *
     * @return Returns the norm of the 3D vector in parameter.
     */
    static double getNorm(const Matrix& a);

    /**
     * @brief Normalize a 3D vector.
     *
     * Be careful, this only works with 3D vector.
     *
     * @param a The 3D vector.
     *
     * @return Returns a new 3D vector which is the normalized vector of a.
     *
     * @see getNorm
     */
    static Matrix normalize(const Matrix& a);

    /**
     * @brief Invert the matrix in parameter (only for a 3*3 matrix).
     *
     * @param a   The matrix we want to invert.
     *
     * @return Returns the inverted matrix.
     *
     * @see transpose
     * @see determinant
     * @see scalarProduct
     */
    static Matrix invert(const Matrix& a);

    /**
     * @brief Get the determinant of a 3*3 matrix.
     *
     * @param a   The matrix we want to have the determinant.
     *
     * @return Returns the determinant of the matrix.
     */
    static double determinant(const Matrix& a);

    /**
    * @brief Get the scalar product of 2 Vec3.
    *
    * @param a   The first vec3.
    * @param b   The second vec3.
    *
    * @return Returns the scalar production of the 2 Vec3.
    */
    static double scalarProduct(const Matrix& a, const Matrix& b);

    /**
     * @brief Reflection implementation.
     *
     * @param originPrimary      The origin point of the primary ray.
     * @param directionPrimary   The direction of the primary ray.
     * @param intersectionPoint  The intersection point.
     * @param intersectionNormal The intersection normal.
     *
     * @return Returns the reflected ray direction. The reflected ray will be intersectionPoint + reflectedDirection.
     */
    static Matrix reflection(const Matrix& directionPrimary, const Matrix& intersectionNormal);

    /**
     * @brief Round a matrix.
     *
     * @param matrix The matrix to round.
     *
     * @return Returns the rounded matrix.
     */
    static Matrix round(const Matrix& matrix);

    /**
     * @brief Test if two matrices are approximately equal.
     *
     * @param a         The first matrix to compare.
     * @param b         The second matrix to compare.
     * @param precision The precision of the comparison, a ~= b +- precision.
     *
     * @return Returns true if a and b are approximately equal.
     */
    static bool areApproximatelyEqual(const Matrix& a, const Matrix& b, double precision = 0.01);

protected:
    /**
     * @brief Allocate the matrix.
     *
     * @param rowCount    The matrix row count.
     * @param columnCount The matrix column count.
     */
    void allocate(std::size_t rowCount, std::size_t columnCount);

    /**
     * @brief Deallocate the matrix.
     */
    void deallocate();

    /**
     * @brief Fill the matrix from an initializer list.
     *
     * @param initializerList The initializer list.
     */
    void fill(const std::initializer_list<std::initializer_list<double>>& initializerList);

    /**
     * @brief Fill the matrix from another matrix.
     *
     * @param a The matrix to fill from.
     */
    void fill(const Matrix& a);

    /**
     * @brief Fill the matrix with a specific value.
     *
     * @param value The value to use.
     */
    void fill(double value);

private:
    /**
     * The number of the line of our matrix.
     */
    std::size_t m_rowCount = 0;

    /**
     * The number of the column of our matrix.
     */
    std::size_t m_columnCount = 0;

    /**
     * Store the element of our matrix.
     */
    double** m_matrix = nullptr;
};

#endif //H_RAYTRACING_MATRIX_H
