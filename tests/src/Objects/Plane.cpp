#include <Objects/Plane.h>
#include <doctest.h>

TEST_CASE("Testing plane object")
{
    Vector3 coordinates({{1, 1, 0}});
    Color color{};
    Plane plane(color, coordinates, 3);

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

    Vector3 light({{5, 5, 5}});

    // 6 Rays to test the result of getSecondaryRay
    Ray s1(plane.getIntersection(r1).value(), (light - plane.getIntersection(r1).value()).toVector3(), SECONDARY);
    Ray s1prime(plane.getIntersection(r1).value(), (light - plane.getIntersection(r1).value()).toVector3(), PRIMARY);

    Ray s2(plane.getIntersection(r1).value(), (plane.getIntersection(r1).value() - light).toVector3(), SECONDARY);
    Ray s2prime(plane.getIntersection(r1).value(), (plane.getIntersection(r1).value() - light).toVector3(), PRIMARY);

    Ray s3(plane.getIntersection(r1).value(), (light - plane.getIntersection(r1).value()).toVector3(), SECONDARY);
    Ray s3prime(plane.getIntersection(r1).value(), (plane.getIntersection(r1).value() - light).toVector3(), SECONDARY);

    // Test if there is an intersection point found
    CHECK(plane.getSecondaryRay(plane.getIntersection(r1).value(), light) == s1);
    CHECK(plane.getSecondaryRay(plane.getIntersection(r1).value(), light) != s1prime);
    CHECK(plane.getSecondaryRay(plane.getIntersection(r1).value(), light) != s2);
    CHECK(plane.getSecondaryRay(plane.getIntersection(r1).value(), light) != s2prime);
    CHECK(plane.getSecondaryRay(plane.getIntersection(r1).value(), light) == s3);
    CHECK(plane.getSecondaryRay(plane.getIntersection(r1).value(), light) != s3prime);
}