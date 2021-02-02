#include <Objects/Plane.h>
#include <doctest.h>

TEST_CASE("Testing plane object")
{
    Vector3 coordinates({{1, 1, 0}});
    Color color{};
    Plane plane(coordinates, color, 3);

    Vector3 a1({{1.5, 1.5, 3}});
    Ray r1({{0, 0, 0}}, a1, PRIMARY);
    Vector3 res1({{1.5, 1.5, 3}});

    Vector3 a2({{0, 3, 0}});
    Ray r2({{0, 0, 0}}, a2, PRIMARY);
    Vector3 res2({{0, 3, 0}});

    Vector3 a3({{-1.5, 1.5, 0}});
    Ray r3({{0, 0, 0}}, a3, PRIMARY);

    Vector3 a4({{0, 3, 0}});
    Ray r4({{0, 0, 0}}, a4, SECONDARY);

    Vector3 a5({{-1, -1, 0}});
    Ray r5({{0, 0, 0}}, a5, PRIMARY);

    CHECK(Matrix::areApproximatelyEqual(plane.getIntersection(r1).value(), res1));
    CHECK(Matrix::areApproximatelyEqual(plane.getIntersection(r2).value(), res2));
    CHECK(plane.getIntersection(r3) == std::nullopt);
    CHECK(plane.getIntersection(r4) == std::nullopt);
    CHECK(plane.getIntersection(r5) == std::nullopt);
}