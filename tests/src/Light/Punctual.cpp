#include <Light/Punctual.h>
#include <doctest.h>

TEST_CASE("Testing punctual light")
{
    Vector3 origin({{0, 0, 0}});
    Vector3 direction({{0.75, 0.75, 1}});

    Punctual punctual({10, Colors::white(), origin});

    Vector3 r1({{1, 1, 1}});
    Vector3 r2({{1, 1, 1.5}});
    Vector3 r3({{1.5, 0.5, 1}});
    Vector3 r4({{1.25, 0.75, 1}});
    Vector3 r5({{0.75, 1.25, 1}});
    Vector3 r7({{-0.25, -0.75, -1}});

    // Check if the device if in the light
    CHECK(punctual.isEnLight(r1) == true);
    CHECK(punctual.isEnLight(r2) == true);
    CHECK(punctual.isEnLight(r3) == true);
    CHECK(punctual.isEnLight(r4) == true);
    CHECK(punctual.isEnLight(r5) == true);
    CHECK(punctual.isEnLight(r7) == true);

    // Check if the origin point found is correct
    CHECK(punctual.getOrigin(r1) == origin);
    CHECK(punctual.getOrigin(r2) == origin);
    CHECK(punctual.getOrigin(r3) == origin);
    CHECK(punctual.getOrigin(r4) == origin);
    CHECK(punctual.getOrigin(r5) == origin);
    CHECK(punctual.getOrigin(r7) == origin);

    // Check if the direction is correct
    CHECK(punctual.getDirection(r1) == (origin - r1));
    CHECK(punctual.getDirection(r2) == (origin - r2));
    CHECK(punctual.getDirection(r3) == (origin - r3));
    CHECK(punctual.getDirection(r4) == (origin - r4));
    CHECK(punctual.getDirection(r5) == (origin - r5));
    CHECK(punctual.getDirection(r7) == (origin - r7));
}