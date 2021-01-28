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

TEST_CASE("testing example")
{

    /* Init test */
    Matrix a(2, 2, {{1, 0}, {0, 1}});

    CHECK(a.getValue(0, 0) == 1);
    CHECK(a.getValue(0, 1) == 0);
    CHECK(a.getValue(1, 0) == 0);
    CHECK(a.getValue(1, 1) == 1);

    Matrix b(2, 2, {{0, 1}, {1, 0}});
    Matrix b2(2, 2, {{-3, -2}, {-2, 6}});
    Matrix b3(2, 2, {{1.25, -5.25}, {-1.33, 0.33}});

    Matrix vec3(3, 1, {{3}, {5}, {0.2}});
    Matrix vec31(3, 1, {{0}, {1}, {0}});

    /* Addition tests */
    Matrix c = Matrix::addMat(a, b);
    Matrix c2 = Matrix::addMat(a, b2);
    Matrix c3 = Matrix::addMat(a, b3);

    // Positive value
    CHECK(c.getValue(0, 0) == 1);
    CHECK(c.getValue(0, 1) == 1);
    CHECK(c.getValue(1, 0) == 1);
    CHECK(c.getValue(1, 1) == 1);

    // Negative value
    CHECK(c2.getValue(0, 0) == -2);
    CHECK(c2.getValue(0, 1) == -2);
    CHECK(c2.getValue(1, 0) == -2);
    CHECK(c2.getValue(1, 1) == 7);

    // float
    CHECK(c3.getValue(0, 0) == 2.25);
    CHECK(c3.getValue(0, 1) == -5.25);
    CHECK(c3.getValue(1, 0) == -1.33);
    CHECK(c3.getValue(1, 1) == 1.33);

    /* Subtraction tests */
    Matrix d = Matrix::subMat(a, b);
    Matrix d2 = Matrix::subMat(a, b2);
    Matrix d3 = Matrix::subMat(a, b3);

    CHECK(d.getValue(0, 0) == 1);
    CHECK(d.getValue(0, 1) == -1);
    CHECK(d.getValue(1, 0) == -1);
    CHECK(d.getValue(1, 1) == 1);

    CHECK(d2.getValue(0, 0) == 4);
    CHECK(d2.getValue(0, 1) == 2);
    CHECK(d2.getValue(1, 0) == 2);
    CHECK(d2.getValue(1, 1) == -5);

    CHECK(absoluteToleranceCompare(d3.getValue(0, 0), -0.25));
    CHECK(absoluteToleranceCompare(d3.getValue(0, 1), 5.25));
    CHECK(absoluteToleranceCompare(d3.getValue(1, 0), 1.33));
    CHECK(absoluteToleranceCompare(d3.getValue(1, 1), 0.67));

    /* Multiplication with scalar */
    Matrix e = Matrix::scalMult(a, 7);
    Matrix e2 = Matrix::scalMult(a, -7);
    Matrix e3 = Matrix::scalMult(a, 0.33);

    CHECK(e.getValue(0, 0) == 7);
    CHECK(e.getValue(0, 1) == 0);
    CHECK(e.getValue(1, 0) == 0);
    CHECK(e.getValue(1, 1) == 7);

    CHECK(e2.getValue(0, 0) == -7);
    CHECK(e2.getValue(0, 1) == 0);
    CHECK(e2.getValue(1, 0) == 0);
    CHECK(e2.getValue(1, 1) == -7);

    CHECK(absoluteToleranceCompare(e3.getValue(0, 0), 0.33));
    CHECK(absoluteToleranceCompare(e3.getValue(0, 1), 0));
    CHECK(absoluteToleranceCompare(e3.getValue(1, 0), 0));
    CHECK(absoluteToleranceCompare(e3.getValue(1, 1), 0.33));

    /* Multiplication with another matrix */
    Matrix f = Matrix::prodMat(a, a);
    Matrix f2 = Matrix::prodMat(a, b);
    Matrix f3 = Matrix::prodMat(b2, b3);

    CHECK(f.getValue(0, 0) == 1);
    CHECK(f.getValue(0, 1) == 0);
    CHECK(f.getValue(1, 0) == 0);
    CHECK(f.getValue(1, 1) == 1);

    CHECK(f2.getValue(0, 0) == 0);
    CHECK(f2.getValue(0, 1) == 1);
    CHECK(f2.getValue(1, 0) == 1);
    CHECK(f2.getValue(1, 1) == 0);

    CHECK(absoluteToleranceCompare(f3.getValue(0, 0), -1.09));
    CHECK(absoluteToleranceCompare(f3.getValue(0, 1), 15.09));
    CHECK(absoluteToleranceCompare(f3.getValue(1, 0), -10.48));
    CHECK(absoluteToleranceCompare(f3.getValue(1, 1), 12.48));

    /* Rotation X, Y and Z */
    Matrix g = Matrix::rotationX(0.25, vec3);
    Matrix g2 = Matrix::rotationY(0.25, vec3);
    Matrix g3 = Matrix::rotationZ(0.25, vec3);

    CHECK(absoluteToleranceCompare(g.getValue(0, 0), 3));
    CHECK(approximatelyEqual(g.getValue(1, 0), 4.79508));
    CHECK(approximatelyEqual(g.getValue(2, 0), 1.4308022806));

    CHECK(approximatelyEqual(g2.getValue(0, 0), 2.95622));
    CHECK(approximatelyEqual(g2.getValue(1, 0), 5));
    CHECK(approximatelyEqual(g2.getValue(2, 0), -0.548429));

    CHECK(approximatelyEqual(g3.getValue(0, 0), 1.66972));
    CHECK(approximatelyEqual(g3.getValue(1, 0), 5.58677));
    CHECK(approximatelyEqual(g3.getValue(2, 0), 0.2));

    /* Matrix transposition */
    Matrix h = Matrix::transposed(a);
    Matrix h1 = Matrix::transposed(vec3);
    Matrix h2 = Matrix::transposed(b3);

    CHECK(h.getValue(0, 0) == 1);
    CHECK(h.getValue(0, 1) == 0);
    CHECK(h.getValue(1, 0) == 0);
    CHECK(h.getValue(1, 1) == 1);

    CHECK(h1.getValue(0, 0) == 3);
    CHECK(h1.getValue(0, 1) == 5);
    CHECK(h1.getValue(0, 2) == 0.2);

    CHECK(h2.getValue(0, 0) == 1.25);
    CHECK(h2.getValue(0, 1) == -1.33);
    CHECK(h2.getValue(1, 0) == -5.25);
    CHECK(h2.getValue(1, 1) == 0.33);

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
}