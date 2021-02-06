#ifndef H_RAYTRACING_UTILS_H
#define H_RAYTRACING_UTILS_H

#include <cstdint>

/**
 * @enum Endian
 * @brief Possible endianness value (big and little).
 */
enum class Endian
{
    BIG = 0,   /*!< Big endian. */
    LITTLE = 1 /*!< Little endian. */
};

/**
 * @brief Get the endianness of the current system (at runtime).
 *
 * @return Returns Endian::BIG or Endian::LITTLE.
 */
Endian endianness();

inline constexpr double pow2(double value)
{
    return value * value;
}

#endif //H_RAYTRACING_UTILS_H
