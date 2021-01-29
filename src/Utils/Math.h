#ifndef H_RAYTRACING_MATH_H
#define H_RAYTRACING_MATH_H

/**
 * @brief Check if two double numbers are approximately equal.
 *
 * @param a       First number to compare.
 * @param b       Second number to compare.
 * @param epsilon The precision value, a ~= b +- epsilon.
 *
 * @return Returns true if the two double numbers are approximately equal (+- epsilon).
 */
bool areDoubleApproximatelyEqual(double a, double b, double epsilon = 0.001);

/**
 * @brief Check if two double numbers are equal.
 *
 * @param x First number to compare.
 * @param y Second number to compare.
 *
 * @return Returns true if the two double numbers are equal.
 */
bool areDoubleEqual(double x, double y);

#endif //H_RAYTRACING_MATH_H
