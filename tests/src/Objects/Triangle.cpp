#include <Objects/Triangle.h>
#include <doctest.h>

TEST_CASE("Testing triangle object")
{
    Vector3 coordinates({{1, 1, 0}});

    Vector3 originA({0, 0, 3});
    Vector3 originB({-1, 1, 0});
    Vector3 originC({1, -1, 0});

    Color color{};
    Triangle triangle(Materials::metal(), color, originA + coordinates, originB + coordinates, originC + coordinates);

    Vector3 a1({{1, 1, 0}});
    Ray r1({{0, 0, 0}}, a1, PRIMARY);

    Vector3 a2({{1, 1, 3}});
    Ray r2({{0, 0, 0}}, a2, PRIMARY);

    Vector3 a3({{0, 2, 0}});
    Ray r3({{0, 0, 0}}, a3, PRIMARY);

    Vector3 a4({{2, 0, 0}});
    Ray r4({{0, 0, 0}}, a4, PRIMARY);

    Vector3 a5({{1, 1, 1}});
    Ray r5({{0, 0, 0}}, a5, PRIMARY);

    Vector3 a6({{1, 1, 4}});
    Ray r6({{0, 0, 0}}, a6, PRIMARY);

    Vector3 a7({{-1, 3, 0}});
    Ray r7({{0, 0, 0}}, a7, PRIMARY);

    Vector3 a8({{3, -1, 0}});
    Ray r8({{0, 0, 0}}, a8, PRIMARY);

    Vector3 a9({{-2, 0, 0}});
    Ray r9({{0, 0, 0}}, a9, PRIMARY);

    Vector3 a10({{0, -2, 0}});
    Ray r10({{0, 0, 0}}, a10, PRIMARY);

    Vector3 a11({{-2, -2, 0}});
    Ray r11({{0, 0, 0}}, a11, PRIMARY);

    CHECK(triangle.getIntersection(r1).value() == a1);
    CHECK(triangle.getIntersection(r2).value() == a2);
    CHECK(triangle.getIntersection(r3).value() == a3);
    CHECK(triangle.getIntersection(r4).value() == a4);
    CHECK(triangle.getIntersection(r5).value() == a5);
    CHECK(triangle.getIntersection(r6) == std::nullopt);
    CHECK(triangle.getIntersection(r7) == std::nullopt);
    CHECK(triangle.getIntersection(r8) == std::nullopt);
    CHECK(triangle.getIntersection(r9) == std::nullopt);
    CHECK(triangle.getIntersection(r10) == std::nullopt);
    CHECK(triangle.getIntersection(r11) == std::nullopt);

    Vector3 light({{5, 5, 5}});

    // 6 Rays to test the result of getSecondaryRay
    Ray s1(triangle.getIntersection(r1).value(), (light - triangle.getIntersection(r1).value()).toVector3(), SECONDARY);
    Ray s1prime(triangle.getIntersection(r1).value(),
                (light - triangle.getIntersection(r1).value()).toVector3(),
                PRIMARY);

    Ray s2(triangle.getIntersection(r1).value(), (triangle.getIntersection(r1).value() - light).toVector3(), SECONDARY);
    Ray s2prime(triangle.getIntersection(r1).value(),
                (triangle.getIntersection(r1).value() - light).toVector3(),
                PRIMARY);

    Ray s3(triangle.getIntersection(r1).value(), (light - triangle.getIntersection(r1).value()).toVector3(), SECONDARY);
    Ray s3prime(triangle.getIntersection(r1).value(),
                (triangle.getIntersection(r1).value() - light).toVector3(),
                SECONDARY);

    // Test if there is an intersection point found
    CHECK(triangle.getSecondaryRay(triangle.getIntersection(r1).value(), light) == s1);
    CHECK(triangle.getSecondaryRay(triangle.getIntersection(r1).value(), light) != s1prime);
    CHECK(triangle.getSecondaryRay(triangle.getIntersection(r1).value(), light) != s2);
    CHECK(triangle.getSecondaryRay(triangle.getIntersection(r1).value(), light) != s2prime);
    CHECK(triangle.getSecondaryRay(triangle.getIntersection(r1).value(), light) == s3);
    CHECK(triangle.getSecondaryRay(triangle.getIntersection(r1).value(), light) != s3prime);

    Vector3 u = originC - originA;
    Vector3 v = originB - originA;

    Vector3 normal = Matrix::vectProduct(u, v) * -1;

    CHECK(triangle.getNormal(triangle.getIntersection(r1).value()) == normal);
    CHECK(triangle.getNormal(triangle.getIntersection(r2).value()) == normal);
    CHECK(triangle.getNormal(triangle.getIntersection(r3).value()) == normal);
    CHECK(triangle.getNormal(triangle.getIntersection(r4).value()) == normal);
    CHECK(triangle.getNormal(triangle.getIntersection(r5).value()) == normal);

    CHECK(triangle.getRefractedIntersection(r1).value() == a1);
    CHECK(triangle.getRefractedIntersection(r2).value() == a2);
    CHECK(triangle.getRefractedIntersection(r3).value() == a3);
    CHECK(triangle.getRefractedIntersection(r4).value() == a4);
    CHECK(triangle.getRefractedIntersection(r5).value() == a5);
    CHECK(triangle.getRefractedIntersection(r6) == std::nullopt);
    CHECK(triangle.getRefractedIntersection(r7) == std::nullopt);
    CHECK(triangle.getRefractedIntersection(r8) == std::nullopt);
    CHECK(triangle.getRefractedIntersection(r9) == std::nullopt);
    CHECK(triangle.getRefractedIntersection(r10) == std::nullopt);
    CHECK(triangle.getRefractedIntersection(r11) == std::nullopt);
}
