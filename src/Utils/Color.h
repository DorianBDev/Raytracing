#ifndef H_RAYTRACING_COLOR_H
#define H_RAYTRACING_COLOR_H

#include <cstdint>

/**
 * @struct Color
 * @brief Color base class.
 *
 * @see Matrix
 */
struct Color
{
    /**
     * @brief Create default color.
     */
    constexpr Color() = default;

    /**
     * @brief Create a new color object.
     *
     * @param red   The red channel value ([0;255]).
     * @param green The green channel value ([0;255]).
     * @param blue  The blue channel value ([0;255]).
     * @param alpha The alpha channel value ([0;255]).
     */
    constexpr Color(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha = 255)
        : m_red(red),
          m_green(green),
          m_blue(blue),
          m_alpha(alpha)
    {
    }

    /**
     * @brief Set the color.
     *
     * @param red   The red channel value ([0;255]).
     * @param green The green channel value ([0;255]).
     * @param blue  The blue channel value ([0;255]).
     * @param alpha The alpha channel value ([0;255]).
     */
    void setColor(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha = 255)
    {
        m_red = red;
        m_green = green;
        m_blue = blue;
        m_alpha = alpha;
    }

    /**
     * @brief Get the red color channel.
     *
     * @return Returns the red color channel.
     */
    uint8_t red() const
    {
        return m_red;
    }

    /**
     * @brief Get the green color channel.
     *
     * @return Returns the green color channel.
     */
    uint8_t green() const
    {
        return m_green;
    }

    /**
     * @brief Get the blue color channel.
     *
     * @return Returns the blue color channel.
     */
    uint8_t blue() const
    {
        return m_blue;
    }

    /**
     * @brief Get the alpha color channel.
     *
     * @return Returns the alpha color channel.
     */
    uint8_t alpha() const
    {
        return m_alpha;
    }

private:
    uint8_t m_red = 0;
    uint8_t m_green = 0;
    uint8_t m_blue = 0;
    uint8_t m_alpha = 0;
};

/**
 * @brief Define usual colors.
 */
namespace Colors
{
    constexpr Color red()
    {
        return Color(255, 0, 0);
    }

    constexpr Color green()
    {
        return Color(0, 255, 0);
    }

    constexpr Color blue()
    {
        return Color(0, 0, 255);
    }

    constexpr Color black()
    {
        return Color(0, 0, 0);
    }

    constexpr Color white()
    {
        return Color(255, 255, 255);
    }
} // namespace Colors

#endif //H_RAYTRACING_COLOR_H
