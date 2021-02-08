#include <Light/Directional.h>
#include <doctest.h>

TEST_CASE("Testing directional light")
{
    Vector3 originA({{0.5, 0, 0}});
    Vector3 originB({{0, 0.5, 0}});
    Vector3 direction({{0.75, 0.75, 1}});

    Directional directional({10, Colors::white(), originA, originB, direction});

    Vector3 a1({{1, 1, 1}});
    Vector3 a2({{1, 1, 1.5}});
    Vector3 a3({{1.5, 0.5, 1}});
    Vector3 a4({{1.25, 0.75, 1}});
    Vector3 a5({{0.75, 1.25, 1}});
    Vector3 a7({{-0.25, -0.75, -1}});

    // Check if the device if in the light
    CHECK(directional.isEnLight(a1) == true);
    CHECK(directional.isEnLight(a2) == false);
    CHECK(directional.isEnLight(a3) == false);
    CHECK(directional.isEnLight(a4) == true);
    CHECK(directional.isEnLight(a5) == true);
    CHECK(directional.isEnLight(a7) == false);

    Vector3 o1({{0.25, 0.25, 0}});
    Vector3 o4({{0.5, 0, 0}});
    Vector3 o5({{0, 0.5, 0}});

    // Check if the origin point found is correct
    CHECK(directional.getOrigin(a1) == o1);
    CHECK(directional.getOrigin(a2) == std::nullopt);
    CHECK(directional.getOrigin(a3) == std::nullopt);
    CHECK(directional.getOrigin(a4) == o4);
    CHECK(directional.getOrigin(a5) == o5);
    CHECK(directional.getOrigin(a7) == std::nullopt);

    // Check if the direction is correct
    CHECK(directional.getDirection(a1) == (direction - a1));
    CHECK(directional.getDirection(a4) == (direction - a4));
    CHECK(directional.getDirection(a5) == (direction - a5));
}