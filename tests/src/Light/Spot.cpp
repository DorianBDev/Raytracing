#include <Light/Spot.h>
#include <doctest.h>

TEST_CASE("Testing spot light")
{
    Vector3 origin({{0, 0, 0}});
    Vector3 direction({{0, 2, 0}});

    Spot spot({10, Colors::white(), origin, direction, 45});

    Vector3 r1({{0, 2, 0}});
    Vector3 r2({{2, 2, 0}});
    Vector3 r3({{-2, 2, 0}});
    Vector3 r4({{0, 2, 2}});
    Vector3 r5({{0, 2, -2}});
    Vector3 r6({{-0.7, 2, 0}});
    Vector3 r7({{-1.6, 0.6, 0}});
    Vector3 r8({{1.6, 0.6, 0}});
    Vector3 r9({{0, -2, 0}});

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

    CHECK(spot.getDirection(r1) == (origin - r1));
    CHECK(spot.getDirection(r2) == (origin - r2));
    CHECK(spot.getDirection(r3) == (origin - r3));
    CHECK(spot.getDirection(r4) == (origin - r4));
    CHECK(spot.getDirection(r5) == (origin - r5));
    CHECK(spot.getDirection(r6) == (origin - r6));
}