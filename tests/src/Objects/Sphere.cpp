#include <Objects/Sphere.h>
#include <doctest.h>

TEST_CASE("testing sphere")
{
    Vector3 coordinates({{1, 1, 1}});
    Color color{};
    Sphere sphere(coordinates, color, 1);

    // b = (0, 0, 0)
    // y = a_i * x + b

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

    sphere.getIntersection(r1).value().print();
    sphere.getIntersection(r2).value().print();
    //sphere.getIntersection(r3).value().print();
    //sphere.getIntersection(r4).value().print();
    sphere.getIntersection(r5).value().print();

    CHECK(Matrix::areApproximatelyEqual(sphere.getIntersection(r1).value(), res1)); // OK
    CHECK(Matrix::areApproximatelyEqual(sphere.getIntersection(r2).value(), res2)); // OK
    CHECK(sphere.getIntersection(r3) == std::nullopt);                              // NO
    CHECK(sphere.getIntersection(r4) == std::nullopt);                              // NO
    CHECK(Matrix::areApproximatelyEqual(sphere.getIntersection(r5).value(), res5)); // OK
}