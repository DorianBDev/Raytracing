#include <Utils/Matrix.h>
#include <cmath>
#include <doctest.h>

bool absoluteToleranceCompare(double x, double y)
{
    return std::fabs(x - y) <= std::numeric_limits<double>::epsilon();
}

bool approximatelyEqual(double a, double b, double epsilon = 0.01)
{
    return std::fabs(a - b) <= ((std::fabs(a) < std::fabs(b) ? std::fabs(b) : std::fabs(a)) * epsilon);
}

TEST_CASE("testing matrix 1")
{

    /* Init test */
    Matrix a(2, 2, {{1, 0}, {0, 1}});

    CHECK(a.value(0, 0) == 1);
    CHECK(a.value(0, 1) == 0);
    CHECK(a.value(1, 0) == 0);
    CHECK(a.value(1, 1) == 1);

    Matrix b(2, 2, {{0, 1}, {1, 0}});
    Matrix b2(2, 2, {{-3, -2}, {-2, 6}});
    Matrix b3(2, 2, {{1.25, -5.25}, {-1.33, 0.33}});

    Matrix vec3(3, 1, {{3}, {5}, {0.2}});
    Matrix vec31(3, 1, {{0}, {1}, {0}});

    Matrix calcDet(3, 3, {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}});
    Matrix calcDet2(3, 3, {{1, 0.25, 2}, {3, 1, 2}, {0.4, 0.7, 1}});

    /* Addition tests */
    Matrix c = Matrix::addMatrix(a, b);
    Matrix c2 = Matrix::addMatrix(a, b2);
    Matrix c3 = Matrix::addMatrix(a, b3);

    // Positive value
    CHECK(c.value(0, 0) == 1);
    CHECK(c.value(0, 1) == 1);
    CHECK(c.value(1, 0) == 1);
    CHECK(c.value(1, 1) == 1);

    // Negative value
    CHECK(c2.value(0, 0) == -2);
    CHECK(c2.value(0, 1) == -2);
    CHECK(c2.value(1, 0) == -2);
    CHECK(c2.value(1, 1) == 7);

    // float
    CHECK(c3.value(0, 0) == 2.25);
    CHECK(c3.value(0, 1) == -5.25);
    CHECK(c3.value(1, 0) == -1.33);
    CHECK(c3.value(1, 1) == 1.33);

    /* Subtraction tests */
    Matrix d = Matrix::subMatrix(a, b);
    Matrix d2 = Matrix::subMatrix(a, b2);
    Matrix d3 = Matrix::subMatrix(a, b3);

    CHECK(d.value(0, 0) == 1);
    CHECK(d.value(0, 1) == -1);
    CHECK(d.value(1, 0) == -1);
    CHECK(d.value(1, 1) == 1);

    CHECK(d2.value(0, 0) == 4);
    CHECK(d2.value(0, 1) == 2);
    CHECK(d2.value(1, 0) == 2);
    CHECK(d2.value(1, 1) == -5);

    CHECK(absoluteToleranceCompare(d3.value(0, 0), -0.25));
    CHECK(absoluteToleranceCompare(d3.value(0, 1), 5.25));
    CHECK(absoluteToleranceCompare(d3.value(1, 0), 1.33));
    CHECK(absoluteToleranceCompare(d3.value(1, 1), 0.67));

    /* Multiplication with scalar */
    Matrix e = Matrix::scalarProduct(a, 7);
    Matrix e2 = Matrix::scalarProduct(a, -7);
    Matrix e3 = Matrix::scalarProduct(a, 0.33);

    CHECK(e.value(0, 0) == 7);
    CHECK(e.value(0, 1) == 0);
    CHECK(e.value(1, 0) == 0);
    CHECK(e.value(1, 1) == 7);

    CHECK(e2.value(0, 0) == -7);
    CHECK(e2.value(0, 1) == 0);
    CHECK(e2.value(1, 0) == 0);
    CHECK(e2.value(1, 1) == -7);

    CHECK(absoluteToleranceCompare(e3.value(0, 0), 0.33));
    CHECK(absoluteToleranceCompare(e3.value(0, 1), 0));
    CHECK(absoluteToleranceCompare(e3.value(1, 0), 0));
    CHECK(absoluteToleranceCompare(e3.value(1, 1), 0.33));

    /* Multiplication with another matrix */
    Matrix f = Matrix::matrixProduct(a, a);
    Matrix f2 = Matrix::matrixProduct(a, b);
    Matrix f3 = Matrix::matrixProduct(b2, b3);

    CHECK(f.value(0, 0) == 1);
    CHECK(f.value(0, 1) == 0);
    CHECK(f.value(1, 0) == 0);
    CHECK(f.value(1, 1) == 1);

    CHECK(f2.value(0, 0) == 0);
    CHECK(f2.value(0, 1) == 1);
    CHECK(f2.value(1, 0) == 1);
    CHECK(f2.value(1, 1) == 0);

    CHECK(absoluteToleranceCompare(f3.value(0, 0), -1.09));
    CHECK(absoluteToleranceCompare(f3.value(0, 1), 15.09));
    CHECK(absoluteToleranceCompare(f3.value(1, 0), -10.48));
    CHECK(absoluteToleranceCompare(f3.value(1, 1), 12.48));

    /* Rotation X, Y and Z */
    Matrix g = Matrix::rotationX(0.25, vec3);
    Matrix g2 = Matrix::rotationY(0.25, vec3);
    Matrix g3 = Matrix::rotationZ(0.25, vec3);

    CHECK(absoluteToleranceCompare(g.value(0, 0), 3));
    CHECK(approximatelyEqual(g.value(1, 0), 4.79508));
    CHECK(approximatelyEqual(g.value(2, 0), 1.4308022806));

    CHECK(approximatelyEqual(g2.value(0, 0), 2.95622));
    CHECK(approximatelyEqual(g2.value(1, 0), 5));
    CHECK(approximatelyEqual(g2.value(2, 0), -0.548429));

    CHECK(approximatelyEqual(g3.value(0, 0), 1.66972));
    CHECK(approximatelyEqual(g3.value(1, 0), 5.58677));
    CHECK(approximatelyEqual(g3.value(2, 0), 0.2));

    /* Matrix transposition */
    Matrix h = Matrix::transposed(a);
    Matrix h1 = Matrix::transposed(vec3);
    Matrix h2 = Matrix::transposed(b3);

    CHECK(h.value(0, 0) == 1);
    CHECK(h.value(0, 1) == 0);
    CHECK(h.value(1, 0) == 0);
    CHECK(h.value(1, 1) == 1);

    CHECK(h1.value(0, 0) == 3);
    CHECK(h1.value(0, 1) == 5);
    CHECK(h1.value(0, 2) == 0.2);

    CHECK(h2.value(0, 0) == 1.25);
    CHECK(h2.value(0, 1) == -1.33);
    CHECK(h2.value(1, 0) == -5.25);
    CHECK(h2.value(1, 1) == 0.33);

    /* Norm Calculation  */
    double i = Matrix::getNorm(vec31);
    double i2 = Matrix::getNorm(vec3);

    CHECK(i == 1);
    CHECK(approximatelyEqual(i2, 5.8343808583));

    /* Normalize */
    Matrix j = Matrix::normalize(vec31);
    Matrix j2 = Matrix::normalize(vec3);

    CHECK(Matrix::getNorm(j) == 1);
    CHECK(approximatelyEqual(Matrix::getNorm(j2), 1.0));

    /* Determinant */

    CHECK(Matrix::determinant(calcDet) == 0);
    CHECK(approximatelyEqual(Matrix::determinant(calcDet2), 2.45));

    /* Invert */

    Matrix toInvert(3, 3, {{-1, 2, 5}, {1, 2, 3}, {-2, 8, 10}});
    Matrix toTest = toInvert.invert(toInvert);

    CHECK(toTest.value(0, 0) == -0.125);
    CHECK(toTest.value(0, 1) == 0.625);
    CHECK(toTest.value(0, 2) == -0.125);
    CHECK(toTest.value(1, 0) == -0.5);
    CHECK(toTest.value(1, 1) == 0);
    CHECK(toTest.value(1, 2) == 0.25);
    CHECK(toTest.value(2, 0) == 0.375);
    CHECK(toTest.value(2, 1) == 0.125);
    CHECK(toTest.value(2, 2) == -0.125);
}

TEST_CASE("testing matrix 2")
{
    Matrix a = Matrix(2, 2, {{0.41453, 40.888888888888}, {50.695599, 10.1444868644}});

    a.round();
    CHECK(a.value(0, 0) == 0.0);
    CHECK(a.value(0, 1) == 41.0);
    CHECK(a.value(1, 0) == 51.0);
    CHECK(a.value(1, 1) == 10.0);

    //TODO: test operators
    //TODO: test matrix.functions()
    //TODO: test (1,3) and (3,1) for operators
}