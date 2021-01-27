#ifndef H_RAYTRACING_MATRIX_H
#define H_RAYTRACING_MATRIX_H

#include <initializer_list>
#include <iostream>

class Matrix
{
public:
    /* Construct */
    Matrix(std::size_t nbLine, std::size_t nbCol);
    Matrix(std::size_t nbLine,
           std::size_t nbCol,
           const std::initializer_list<std::initializer_list<double>>& initializerList);
    Matrix(const Matrix& /*A*/);

    /* Destruct */
    ~Matrix();

    /* Define value of the matrix */
    void setvalue();

    /* Print */
    void printMatrix();

    /* Addition */
    static Matrix addMat(Matrix& a, Matrix& b);

    /* Substraction */
    static Matrix subMat(Matrix& a, Matrix& b);

    /* Scalar mutliplication */
    static Matrix scalMult(Matrix& a, double scalar);

    /* matrix product */
    static Matrix prodMat(Matrix& a, Matrix& b);

    /* translation  (Vec3) || dependance de AddMat */
    static Matrix translation(Matrix& a, Matrix& b);

    /* Rotation (Vec3)  || dep avec prodMat */
    /*   /!\ To modif    */
    static Matrix rotationX(double alpha, Matrix& a);
    static Matrix rotationY(double alpha, Matrix& a);
    static Matrix rotationZ(double alpha, Matrix& a);

    /* Scale  || dep avec prodMat */
    static Matrix scale(double x, double y, double z, Matrix& a);

    /* Transposition of a matrix*/
    static Matrix transposed(Matrix& a);

    /* Get the norm of a Vec3 (Vec3)*/
    static double getNorm(Matrix& a);

    /* Nomalize a Vec3 || dep with getNorm*/
    static Matrix normalize(Matrix& a);

    double getValue(std::size_t line, std::size_t column);


private:
    std::size_t m_dimL = 0;
    std::size_t m_dimC = 0;

    double** m_matrix = nullptr;
};

#endif //H_LIBTRACE_MATRIX_H
