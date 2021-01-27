#include <Utils/Matrix.h>
#include <doctest.h>

TEST_CASE("testing example")
{
    Matrix a(2, 2, {{1, 0}, {0, 1}});

    CHECK(a.getValue(0, 0) == 1);
    CHECK(a.getValue(0, 1) == 0);
    CHECK(a.getValue(1, 0) == 0);
    CHECK(a.getValue(1, 1) == 1);

    Matrix b(2, 2, {{0, 1}, {1, 0}});
    Matrix c = Matrix::addMat(a, b);

    CHECK(c.getValue(0, 0) == 1);
    CHECK(c.getValue(0, 1) == 1);
    CHECK(c.getValue(1, 0) == 1);
    CHECK(c.getValue(1, 1) == 1);
}