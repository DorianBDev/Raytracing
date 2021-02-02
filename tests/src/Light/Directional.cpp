#include <Light/Directional.h>
#include <doctest.h>

TEST_CASE("Testing directional light")
{
    Vector3 originA({{0.5, 0, 0}});
    Vector3 originB({{0, 0.5, 0}});
    Vector3 direction({{0.75, 0.75, 1}});

    Directional directional({10, originA, originB, direction});

    Ray r1({{1, 1, 1}}, direction, SECONDARY);
    Ray r2({{1, 1, 1.5}}, direction, SECONDARY);
    Ray r3({{1.5, 0.5, 1}}, direction, SECONDARY);
    Ray r4({{1.25, 0.75, 1}}, direction, SECONDARY);
    Ray r5({{0.75, 1.25, 1}}, direction, SECONDARY);
    Ray r6({{0.75, 1.25, 1}}, direction, PRIMARY);
    Ray r7({{-0.25, -0.75, -1}}, direction, SECONDARY);

    // Check if the device if in the light
    CHECK(directional.isEnLight(r1) == true);
    CHECK(directional.isEnLight(r2) == false);
    CHECK(directional.isEnLight(r3) == false);
    CHECK(directional.isEnLight(r4) == true);
    CHECK(directional.isEnLight(r5) == true);
    CHECK(directional.isEnLight(r6) == false);
    CHECK(directional.isEnLight(r7) == false);

    Vector3 o1({{0.25, 0.25, 0}});
    Vector3 o4({{0.5, 0, 0}});
    Vector3 o5({{0, 0.5, 0}});

    // Check if the origin point found is correct
    CHECK(directional.getOrigin(r1) == o1);
    CHECK(directional.getOrigin(r2) == std::nullopt);
    CHECK(directional.getOrigin(r3) == std::nullopt);
    CHECK(directional.getOrigin(r4) == o4);
    CHECK(directional.getOrigin(r5) == o5);
    CHECK(directional.getOrigin(r6) == std::nullopt);
    CHECK(directional.getOrigin(r7) == std::nullopt);

    // Check if the direction is correct
    CHECK(directional.getDirection(r1) == (direction - r1.getOrigin()));
    CHECK(directional.getDirection(r4) == (direction - r4.getOrigin()));
    CHECK(directional.getDirection(r5) == (direction - r5.getOrigin()));
}