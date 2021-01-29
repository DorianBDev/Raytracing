#include <Utils/Vector3.h>
#include <cmath>
#include <doctest.h>
#include <optional>

TEST_CASE("testing vector3")
{
    Vector3 a({1, 2, 3});

    CHECK(a.x() == 1);
    CHECK(a.y() == 2);
    CHECK(a.z() == 3);

    a.setX(4);
    a.setY(5);
    a.setZ(6);

    CHECK(a.x() == 4);
    CHECK(a.y() == 5);
    CHECK(a.z() == 6);

    Vector3 b({2, 0, 0});
    Vector3 c = b.normalize().toVector3();

    CHECK(c.x() == 1);
    CHECK(c.y() == 0);
    CHECK(c.z() == 0);

    Vector3 d;
    d = c + b;

    CHECK(d.x() == 2);
    CHECK(d.y() == 0);
    CHECK(d.z() == 0);

    Matrix m(3, 3, {{1, 1, 1}, {1, 1, 1}, {1, 1, 1}});
    d = b * m + c;

    CHECK(d.x() == 2);
    CHECK(d.y() == 1);
    CHECK(d.z() == 1);

    d = b * 5.0 + c;

    CHECK(d.x() == 6);
    CHECK(d.y() == 0);
    CHECK(d.z() == 0);

    // Vector3(1,3) * Vector3(1,3)
    CHECK_THROWS(b * c);

    // Vector3(3,1) * Vector3(1,3)
    CHECK_NOTHROW(b.transpose() * c);

    // Vector3 = Matrix(1,1)
    CHECK_THROWS(d = b * c);

    b = Vector3({6, 0, 0});

    CHECK(b != c);
    CHECK(b != m);
    CHECK(d == b);

    b = Vector3({1.256, 9.6899, 0.00025});
    CHECK(d != b);

    d = Vector3({1.256, 9.6899, 0.00025});
    CHECK(d == b);

    std::optional<Vector3> res(Vector3({1, 1, 1}));
    CHECK(res.value() == Vector3({1, 1, 1}));

    //TODO: more tests
}