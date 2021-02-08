#include <Light/Spot.h>
#include <doctest.h>

TEST_CASE("Testing spot light")
{
    Vector3 origin({{0, 0, 0}});
    Vector3 direction({{0, 2, 0}});

    Spot spot({10, Colors::white(), origin, direction, 45});

    Ray r1({{0, 2, 0}}, direction, SECONDARY);
    Ray r2({{2, 2, 0}}, direction, SECONDARY);
    Ray r3({{-2, 2, 0}}, direction, SECONDARY);
    Ray r4({{0, 2, 2}}, direction, SECONDARY);
    Ray r5({{0, 2, -2}}, direction, SECONDARY);
    Ray r6({{-0.7, 2, 0}}, direction, SECONDARY);
    Ray r7({{-1.6, 0.6, 0}}, direction, SECONDARY);
    Ray r8({{1.6, 0.6, 0}}, direction, SECONDARY);
    Ray r9({{0, -2, 0}}, direction, SECONDARY);

    CHECK(spot.isEnLight(r1) == true);
    CHECK(spot.isEnLight(r2) == true);
    CHECK(spot.isEnLight(r3) == true);
    CHECK(spot.isEnLight(r4) == true);
    CHECK(spot.isEnLight(r5) == true);
    CHECK(spot.isEnLight(r6) == true);
    CHECK(spot.isEnLight(r7) == false);
    CHECK(spot.isEnLight(r8) == false);
    CHECK(spot.isEnLight(r9) == false);

    CHECK(spot.getOrigin(r1) == origin);
    CHECK(spot.getOrigin(r2) == origin);
    CHECK(spot.getOrigin(r3) == origin);
    CHECK(spot.getOrigin(r4) == origin);
    CHECK(spot.getOrigin(r5) == origin);
    CHECK(spot.getOrigin(r6) == origin);

    CHECK(spot.getDirection(r1) == (origin - r1.getOrigin()));
    CHECK(spot.getDirection(r2) == (origin - r2.getOrigin()));
    CHECK(spot.getDirection(r3) == (origin - r3.getOrigin()));
    CHECK(spot.getDirection(r4) == (origin - r4.getOrigin()));
    CHECK(spot.getDirection(r5) == (origin - r5.getOrigin()));
    CHECK(spot.getDirection(r6) == (origin - r6.getOrigin()));
}