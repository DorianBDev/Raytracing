#include "Math.h"

#include <cmath>
#include <limits>

bool areDoubleApproximatelyEqual(double a, double b, double epsilon)
{
    return std::fabs(a - b) <= ((std::fabs(a) < std::fabs(b) ? std::fabs(b) : std::fabs(a)) * epsilon);
}

bool areDoubleEqual(double x, double y)
{
    return std::fabs(x - y) <= std::numeric_limits<double>::epsilon();
}