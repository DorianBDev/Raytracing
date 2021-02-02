#include <Light/Punctual.h>
#include <doctest.h>

TEST_CASE("Testing punctual light")
{
    Vector3 origin({{0, 0, 0}});
    Vector3 direction({{0.75, 0.75, 1}});

    Punctual punctual({10, origin});

    Ray r1({{1, 1, 1}}, direction, SECONDARY);
    Ray r2({{1, 1, 1.5}}, direction, SECONDARY);
    Ray r3({{1.5, 0.5, 1}}, direction, SECONDARY);
    Ray r4({{1.25, 0.75, 1}}, direction, SECONDARY);
    Ray r5({{0.75, 1.25, 1}}, direction, SECONDARY);
    Ray r6({{0.75, 1.25, 1}}, direction, PRIMARY);
    Ray r7({{-0.25, -0.75, -1}}, direction, SECONDARY);

    // Check if the device if in the light
    CHECK(punctual.isEnLight(r1) == true);
    CHECK(punctual.isEnLight(r2) == true);
    CHECK(punctual.isEnLight(r3) == true);
    CHECK(punctual.isEnLight(r4) == true);
    CHECK(punctual.isEnLight(r5) == true);
    CHECK(punctual.isEnLight(r6) == false);
    CHECK(punctual.isEnLight(r7) == true);

    // Check if the origin point found is correct
    CHECK(punctual.getOrigin(r1) == origin);
    CHECK(punctual.getOrigin(r2) == origin);
    CHECK(punctual.getOrigin(r3) == origin);
    CHECK(punctual.getOrigin(r4) == origin);
    CHECK(punctual.getOrigin(r5) == origin);
    CHECK(punctual.getOrigin(r6) == std::nullopt);
    CHECK(punctual.getOrigin(r7) == origin);

    // Check if the direction is correct
    CHECK(punctual.getDirection(r1) == (origin - r1.getOrigin()));
    CHECK(punctual.getDirection(r2) == (origin - r2.getOrigin()));
    CHECK(punctual.getDirection(r3) == (origin - r3.getOrigin()));
    CHECK(punctual.getDirection(r4) == (origin - r4.getOrigin()));
    CHECK(punctual.getDirection(r5) == (origin - r5.getOrigin()));
    CHECK(punctual.getDirection(r7) == (origin - r7.getOrigin()));
}