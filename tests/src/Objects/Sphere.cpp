#include <Objects/Sphere.h>
#include <doctest.h>

TEST_CASE("testing sphere")
{
    // To test the intersection point found with the primary ray

    Vector3 coordinates({{1, 1, 1}});
    Color color{};
    Sphere sphere(color, coordinates, 1);

    // b = (0, 0, 0)
    // y = a_i * x + b

    // Initialization of 5 rays with their results
    Vector3 a1({{1, 1, 1}});
    Ray r1({{0, 0, 0}}, a1, PRIMARY);
    Vector3 res1({{0.42265, 0.42265, 0.42265}});

    Vector3 a2({{5, 5, 1}});
    Ray r2({{0, 0, 0}}, a2, PRIMARY);
    Vector3 res2({{0.651088, 0.651088, 0.130218}});

    Vector3 a3({{1, -1, 1}});
    Ray r3({{0, 0, 0}}, a3, PRIMARY);

    Vector3 a4({{-1, 1, 1}});
    Ray r4({{0, 0, 0}}, a4, PRIMARY);

    Vector3 a5({{5, 5, 1.5}});
    Ray r5({{0, 0, 0}}, a5, PRIMARY);
    Vector3 res5({{0.60, 0.60, 0.18}});

    CHECK(Matrix::areApproximatelyEqual(sphere.getIntersection(r1).value(), res1));
    CHECK(Matrix::areApproximatelyEqual(sphere.getIntersection(r2).value(), res2));
    CHECK(sphere.getIntersection(r3) == std::nullopt);
    CHECK(sphere.getIntersection(r4) == std::nullopt);
    CHECK(Matrix::areApproximatelyEqual(sphere.getIntersection(r5).value(), res5));

    // The coordinates of the light in the scene
    Vector3 light({{5, 5, 5}});

    // 6 Rays to test the result of getSecondaryRay
    Ray s1(sphere.getIntersection(r1).value(), (light - sphere.getIntersection(r1).value()).toVector3(), SECONDARY);
    Ray s1prime(sphere.getIntersection(r1).value(), (light - sphere.getIntersection(r1).value()).toVector3(), PRIMARY);

    Ray s2(sphere.getIntersection(r1).value(), (sphere.getIntersection(r1).value() - light).toVector3(), SECONDARY);
    Ray s2prime(sphere.getIntersection(r1).value(), (sphere.getIntersection(r1).value() - light).toVector3(), PRIMARY);

    Ray s3(sphere.getIntersection(r1).value(), (light - sphere.getIntersection(r1).value()).toVector3(), SECONDARY);
    Ray s3prime(sphere.getIntersection(r1).value(),
                (sphere.getIntersection(r1).value() - light).toVector3(),
                SECONDARY);

    // Test if there is an intersection point found
    CHECK(sphere.getSecondaryRay(sphere.getIntersection(r1).value(), light) == s1);
    CHECK(sphere.getSecondaryRay(sphere.getIntersection(r1).value(), light) != s1prime);
    CHECK(sphere.getSecondaryRay(sphere.getIntersection(r1).value(), light) != s2);
    CHECK(sphere.getSecondaryRay(sphere.getIntersection(r1).value(), light) != s2prime);
    CHECK(sphere.getSecondaryRay(sphere.getIntersection(r1).value(), light) == s3);
    CHECK(sphere.getSecondaryRay(sphere.getIntersection(r1).value(), light) != s3prime);

    CHECK(Matrix::areApproximatelyEqual(sphere.getNormal(sphere.getIntersection(r1).value()), (res1 - coordinates)));
    CHECK(Matrix::areApproximatelyEqual(sphere.getNormal(sphere.getIntersection(r2).value()), (res2 - coordinates)));
    CHECK(Matrix::areApproximatelyEqual(sphere.getNormal(sphere.getIntersection(r5).value()), (res5 - coordinates)));
}