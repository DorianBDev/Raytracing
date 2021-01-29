#include <Utils/Vector3.h>
#include <cmath>
#include <doctest.h>

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

    //TODO: more tests
}