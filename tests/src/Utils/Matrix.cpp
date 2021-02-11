#include <Utils/Math.h>
#include <Utils/Matrix.h>
#include <doctest.h>

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

    CHECK(areDoubleApproximatelyEqual(d3.value(0, 0), -0.25));
    CHECK(areDoubleApproximatelyEqual(d3.value(0, 1), 5.25));
    CHECK(areDoubleApproximatelyEqual(d3.value(1, 0), 1.33));
    CHECK(areDoubleApproximatelyEqual(d3.value(1, 1), 0.67));

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

    CHECK(areDoubleApproximatelyEqual(e3.value(0, 0), 0.33));
    CHECK(areDoubleApproximatelyEqual(e3.value(0, 1), 0));
    CHECK(areDoubleApproximatelyEqual(e3.value(1, 0), 0));
    CHECK(areDoubleApproximatelyEqual(e3.value(1, 1), 0.33));

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

    CHECK(areDoubleApproximatelyEqual(f3.value(0, 0), -1.09));
    CHECK(areDoubleApproximatelyEqual(f3.value(0, 1), 15.09));
    CHECK(areDoubleApproximatelyEqual(f3.value(1, 0), -10.48));
    CHECK(areDoubleApproximatelyEqual(f3.value(1, 1), 12.48));

    /* Rotation X, Y and Z */
    Matrix g = Matrix::rotationX(0.25, vec3);
    Matrix g2 = Matrix::rotationY(0.25, vec3);
    Matrix g3 = Matrix::rotationZ(0.25, vec3);

    CHECK(areDoubleApproximatelyEqual(g.value(0, 0), 3));
    CHECK(areDoubleApproximatelyEqual(g.value(1, 0), 4.79508));
    CHECK(areDoubleApproximatelyEqual(g.value(2, 0), 1.4308022806));

    CHECK(areDoubleApproximatelyEqual(g2.value(0, 0), 2.95622));
    CHECK(areDoubleApproximatelyEqual(g2.value(1, 0), 5));
    CHECK(areDoubleApproximatelyEqual(g2.value(2, 0), -0.548429));

    CHECK(areDoubleApproximatelyEqual(g3.value(0, 0), 1.66972));
    CHECK(areDoubleApproximatelyEqual(g3.value(1, 0), 5.58677));
    CHECK(areDoubleApproximatelyEqual(g3.value(2, 0), 0.2));

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
    CHECK(areDoubleApproximatelyEqual(i2, 5.8343808583));

    /* Normalize */
    Matrix j = Matrix::normalize(vec31);
    Matrix j2 = Matrix::normalize(vec3);

    CHECK(Matrix::getNorm(j) == 1);
    CHECK(areDoubleApproximatelyEqual(Matrix::getNorm(j2), 1.0));

    /* Determinant */

    CHECK(Matrix::determinant(calcDet) == 0);
    CHECK(areDoubleApproximatelyEqual(Matrix::determinant(calcDet2), 2.45));

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

    Matrix vec32(3, 1, {{1}, {0}, {0}});
    double scalProd = Matrix::dot(vec32, vec32);
    CHECK(scalProd == 1);

    Matrix vec321(3, 1, {{2}, {4}, {6}});
    Matrix vec322(3, 1, {{0.2}, {1}, {3.5}});
    double scalProd2 = Matrix::dot(vec321, vec322);
    CHECK(scalProd2 == 25.4);

    Matrix vec33(1, 3, {{1, 0, 0}});
    double scalProd3 = Matrix::dot(vec33, vec33);
    CHECK(scalProd3 == 1);
}

TEST_CASE("testing matrix 2")
{
    Matrix a = Matrix(2, 2, {{0.41453, 40.888888888888}, {50.695599, 10.1444868644}});

    a.round();
    CHECK(a.value(0, 0) == 0.0);
    CHECK(a.value(0, 1) == 41.0);
    CHECK(a.value(1, 0) == 51.0);
    CHECK(a.value(1, 1) == 10.0);

    Matrix b = Matrix(2, 2, {{0.41453, 40.888888888888}, {50.695599, 10.1444868644}});
    Matrix c = Matrix(2, 2, {{0.41453, 40.888888888888}, {50.695599, 10.1444868644}});
    CHECK(b == c);
    CHECK(Matrix::areApproximatelyEqual(b, c));

    c = Matrix(2, 2, {{0.414531, 40.888888888885}, {50.695599, 10.1444868648}});
    CHECK(b != c);
    CHECK(Matrix::areApproximatelyEqual(b, c));
    CHECK(!Matrix::areApproximatelyEqual(b, c, 0.00000000000000001));

    Matrix a1 = Matrix(2, 2, {{1, 0}, {0, 1}});
    Matrix b1 = Matrix(2, 2, {{0, 1}, {1, 0}});

    /* + */
    Matrix c1 = a1 + b1;
    CHECK(c1.value(0, 0) == 1);
    CHECK(c1.value(0, 1) == 1);
    CHECK(c1.value(1, 0) == 1);
    CHECK(c1.value(1, 1) == 1);

    /* - */
    Matrix c2 = a1 - b1;
    CHECK(c2.value(0, 0) == 1);
    CHECK(c2.value(0, 1) == -1);
    CHECK(c2.value(1, 0) == -1);
    CHECK(c2.value(1, 1) == 1);

    /* *(matrix) */
    Matrix c3 = a1 * b1;
    CHECK(c3.value(0, 0) == 0);
    CHECK(c3.value(0, 1) == 1);
    CHECK(c3.value(1, 0) == 1);
    CHECK(c3.value(1, 1) == 0);

    /* *(scalar) */
    Matrix c4 = a1 * 2;
    //Matrix c4 = 2 * a1; not allowed
    CHECK(c4.value(0, 0) == 2);
    CHECK(c4.value(0, 1) == 0);
    CHECK(c4.value(1, 0) == 0);
    CHECK(c4.value(1, 1) == 2);

    /* += */
    Matrix c5 = Matrix(2, 2, {{1, 0}, {0, 1}});
    c5 += a1;
    CHECK(c5.value(0, 0) == 2);
    CHECK(c5.value(0, 1) == 0);
    CHECK(c5.value(1, 0) == 0);
    CHECK(c5.value(1, 1) == 2);

    /* -= */
    Matrix c6 = Matrix(2, 2, {{1, 0}, {0, 1}});
    c6 -= a1;
    CHECK(c6.value(0, 0) == 0);
    CHECK(c6.value(0, 1) == 0);
    CHECK(c6.value(1, 0) == 0);
    CHECK(c6.value(1, 1) == 0);

    /* *= (matrix) */
    Matrix c7 = a1;
    c7 *= b1;
    CHECK(c7.value(0, 0) == 0);
    CHECK(c7.value(0, 1) == 1);
    CHECK(c7.value(1, 0) == 1);
    CHECK(c7.value(1, 1) == 0);

    /* *= (scalar) */
    Matrix c8 = a1;
    c8 *= 2;
    CHECK(c8.value(0, 0) == 2);
    CHECK(c8.value(0, 1) == 0);
    CHECK(c8.value(1, 0) == 0);
    CHECK(c8.value(1, 1) == 2);

    Matrix d(3, 1, {{3}, {5}, {0.2}});
    Matrix d1(3, 1, {{0}, {1}, {0}});

    d.translate(d1);
    CHECK(d.value(0, 0) == 3);
    CHECK(d.value(1, 0) == 6);
    CHECK(d.value(2, 0) == 0.2);

    Matrix d2(3, 1, {{3}, {5}, {0.2}});

    d2.rotateX(0.25);
    CHECK(areDoubleApproximatelyEqual(d2.value(0, 0), 3));
    CHECK(areDoubleApproximatelyEqual(d2.value(1, 0), 4.79508));
    CHECK(areDoubleApproximatelyEqual(d2.value(2, 0), 1.4308022806));

    Matrix d3(3, 1, {{3}, {5}, {0.2}});
    d3.rotateY(0.25);
    CHECK(areDoubleApproximatelyEqual(d3.value(0, 0), 2.95622));
    CHECK(areDoubleApproximatelyEqual(d3.value(1, 0), 5));
    CHECK(areDoubleApproximatelyEqual(d3.value(2, 0), -0.548429));

    Matrix d4(3, 1, {{3}, {5}, {0.2}});
    d4.rotateZ(0.25);
    CHECK(areDoubleApproximatelyEqual(d4.value(0, 0), 1.66972));
    CHECK(areDoubleApproximatelyEqual(d4.value(1, 0), 5.58677));
    CHECK(areDoubleApproximatelyEqual(d4.value(2, 0), 0.2));

    Matrix d5(3, 1, {{1}, {2}, {3}});
    d5.scale(1, 2, 3);
    CHECK(areDoubleApproximatelyEqual(d5.value(0, 0), 1));
    CHECK(areDoubleApproximatelyEqual(d5.value(1, 0), 4));
    CHECK(areDoubleApproximatelyEqual(d5.value(2, 0), 9));

    d5.transpose();
    CHECK(areDoubleApproximatelyEqual(d5.value(0, 0), 1));
    CHECK(areDoubleApproximatelyEqual(d5.value(0, 1), 4));
    CHECK(areDoubleApproximatelyEqual(d5.value(0, 2), 9));

    Matrix vec3(3, 1, {{3}, {5}, {0.2}});
    double norm = vec3.getNorm();
    CHECK(areDoubleApproximatelyEqual(norm, 5.8343808583));

    vec3.normalize();
    double norm2 = vec3.getNorm();
    CHECK(areDoubleApproximatelyEqual(norm2, 1));

    Matrix calcDet(3, 3, {{1, 0.25, 2}, {3, 1, 2}, {0.4, 0.7, 1}});
    double det = calcDet.determinant();
    CHECK(areDoubleApproximatelyEqual(det, 2.45));

    Matrix toInvert(3, 3, {{-1, 2, 5}, {1, 2, 3}, {-2, 8, 10}});
    toInvert.invert();

    CHECK(toInvert.value(0, 0) == -0.125);
    CHECK(toInvert.value(0, 1) == 0.625);
    CHECK(toInvert.value(0, 2) == -0.125);
    CHECK(toInvert.value(1, 0) == -0.5);
    CHECK(toInvert.value(1, 1) == 0);
    CHECK(toInvert.value(1, 2) == 0.25);
    CHECK(toInvert.value(2, 0) == 0.375);
    CHECK(toInvert.value(2, 1) == 0.125);
    CHECK(toInvert.value(2, 2) == -0.125);

    Matrix e(1, 3, {{3, 5, 0.2}});
    Matrix e1(1, 3, {{0, 1, 0}});

    e.translate(e1);
    CHECK(e.value(0, 0) == 3);
    CHECK(e.value(0, 1) == 6);
    CHECK(e.value(0, 2) == 0.2);

    Matrix e2(1, 3, {{3, 5, 0.2}});
    e2.rotateX(0.25);
    CHECK(areDoubleApproximatelyEqual(e2.value(0, 0), 3));
    CHECK(areDoubleApproximatelyEqual(e2.value(0, 1), 4.79508));
    CHECK(areDoubleApproximatelyEqual(e2.value(0, 2), 1.4308022806));

    Matrix e3(1, 3, {{3, 5, 0.2}});
    e3.rotateY(0.25);
    CHECK(areDoubleApproximatelyEqual(e3.value(0, 0), 2.95622));
    CHECK(areDoubleApproximatelyEqual(e3.value(0, 1), 5));
    CHECK(areDoubleApproximatelyEqual(e3.value(0, 2), -0.548429));

    Matrix e4(1, 3, {{3, 5, 0.2}});
    e4.rotateZ(0.25);
    CHECK(areDoubleApproximatelyEqual(e4.value(0, 0), 1.66972));
    CHECK(areDoubleApproximatelyEqual(e4.value(0, 1), 5.58677));
    CHECK(areDoubleApproximatelyEqual(e4.value(0, 2), 0.2));

    Matrix e5(1, 3, {{1, 2, 3}});
    e5.scale(1, 2, 3);
    CHECK(areDoubleApproximatelyEqual(e5.value(0, 0), 1));
    CHECK(areDoubleApproximatelyEqual(e5.value(0, 1), 4));
    CHECK(areDoubleApproximatelyEqual(e5.value(0, 2), 9));

    Matrix vec32(1, 3, {{3, 5, 0.2}});
    double norm32 = vec32.getNorm();
    CHECK(areDoubleApproximatelyEqual(norm32, 5.8343808583));

    vec32.normalize();
    double norm322 = vec32.getNorm();
    CHECK(areDoubleApproximatelyEqual(norm322, 1));

    Matrix vec323(3, 1, {{1}, {0}, {0}});
    double scalProd = vec323.scalarProduct(vec323);
    CHECK(scalProd == 1);

    Matrix vec321(3, 1, {{2}, {4}, {6}});
    Matrix vec322(3, 1, {{0.2}, {1}, {3.5}});
    double scalProd2 = vec321.scalarProduct(vec322);
    CHECK(scalProd2 == 25.4);

    Matrix vec33(1, 3, {{1, 0, 0}});
    double scalProd3 = vec33.scalarProduct(vec33);
    CHECK(scalProd3 == 1);

    Matrix incident(1, 3, {{-0.34, 2.83, -1}});
    Matrix normal(1, 3, {{-0.03, 0.57, 0.81}});

    Matrix reflected = Matrix::reflection(incident, normal);

    Matrix reflectedTest(1, 3, {{-0.29, 1.90, -2.317}});
    reflectedTest.normalize();

    Matrix vec41(1, 3, {{1, 0, 0}});
    Matrix vec42(1, 3, {{3, 5, 0.2}});
    Matrix testCrossProd = Matrix::vectProduct(vec41, vec42);
    CHECK(testCrossProd.value(0, 0) == 0);
    CHECK(testCrossProd.value(0, 1) == -0.2);
    CHECK(testCrossProd.value(0, 2) == 5);

    vec41.vectProd(vec42);
    CHECK(vec41.value(0, 0) == 0);
    CHECK(vec41.value(0, 1) == -0.2);
    CHECK(vec41.value(0, 2) == 5);
}