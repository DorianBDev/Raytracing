#include <Utils/Math.h>
#include <doctest.h>

TEST_CASE("testing math")
{
    // areDoubleApproximatelyEqual
    CHECK(areDoubleApproximatelyEqual(0.0126, 0.0126, 0.001));
    CHECK(areDoubleApproximatelyEqual(0.0126, 0.0126, 0.000000001));
    CHECK(areDoubleApproximatelyEqual(0.0126, 0.0126, 0.1));
    CHECK(areDoubleApproximatelyEqual(0.0126, 0.0127, 0.01));
    CHECK(!areDoubleApproximatelyEqual(0.0126, 0.0127, 0.0001));
    CHECK(areDoubleApproximatelyEqual(0.01266666, 0.0126, 0.01));
    CHECK(!areDoubleApproximatelyEqual(0.01266666, 0.0126, 0.001));
    CHECK(areDoubleApproximatelyEqual(0.01268, 0.01269, 0.001));
    CHECK(!areDoubleApproximatelyEqual(0.01268, 0.01269, 0.0001));
    CHECK(areDoubleApproximatelyEqual(0.1126, 0.113, 0.01));
    CHECK(areDoubleApproximatelyEqual(0.1, 0.1, 0));

    // areDoubleEqual
    CHECK(areDoubleEqual(0.0126, 0.0126));
    CHECK(areDoubleEqual(1.0, 1.0));
    CHECK(areDoubleEqual(0.1, 0.1));
    CHECK(areDoubleEqual(1000, 1000));
    CHECK(areDoubleEqual(1000.0123456, 1000.0123456));
    CHECK(!areDoubleEqual(0.0126, 0.0127));
    CHECK(!areDoubleEqual(1.0, 1.1));
    CHECK(!areDoubleEqual(0.1, 0.11));
    CHECK(!areDoubleEqual(1000.1, 1000.001));
}