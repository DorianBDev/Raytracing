#ifndef H_RAYTRACING_COLOR_H
#define H_RAYTRACING_COLOR_H

#include <SFML/Graphics/Color.hpp>
#include <cstdint>
#include <iostream>

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
     * @brief Color copy.
     */
    Color(const Color& color)
    {
        m_red = color.m_red;
        m_green = color.m_green;
        m_blue = color.m_blue;
        m_alpha = color.m_alpha;
    }

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

    /**
     * @brief Scalar multiplication on each channel of the color.
     */
    Color operator*(double value) const
    {
        Color res;

        res.setColor(multiplyChannel(m_red, value),
                     multiplyChannel(m_green, value),
                     multiplyChannel(m_blue, value),
                     multiplyChannel(m_alpha, value));

        return res;
    }

    /**
     * @brief Add two colors.
     */
    inline Color operator+(const Color& color) const
    {
        Color res;

        int red = static_cast<int>(m_red) + static_cast<int>(color.red());
        int green = static_cast<int>(m_green) + static_cast<int>(color.green());
        int blue = static_cast<int>(m_blue) + static_cast<int>(color.blue());
        int alpha = static_cast<int>(m_alpha) + static_cast<int>(color.alpha());

        if (red > 255)
            red = 255;

        if (green > 255)
            green = 255;

        if (blue > 255)
            blue = 255;

        if (alpha > 255)
            alpha = 255;

        if (red < 0)
            red = 0;

        if (green < 0)
            green = 0;

        if (blue < 0)
            blue = 0;

        if (alpha < 0)
            alpha = 0;

        res.setColor(static_cast<uint8_t>(red),
                     static_cast<uint8_t>(green),
                     static_cast<uint8_t>(blue),
                     static_cast<uint8_t>(alpha));

        return res;
    }

    /**
     * @brief Add two colors.
     */
    Color& operator+=(const Color& color)
    {
        *this = *this + color;

        return *this;
    }

    Color& operator=(const Color& color)
    {
        if (this == &color)
            return *this;

        m_red = color.m_red;
        m_green = color.m_green;
        m_blue = color.m_blue;
        m_alpha = color.m_alpha;

        return *this;
    }

    /**
     * @brief Convert the color to sf::Color.
     */
    sf::Color toSFMLColor() const
    {
        return sf::Color(m_red, m_green, m_blue, m_alpha);
    }

    /**
     * @brief Print color.
     */
    void print() const
    {
        std::cout << "Color("                          //
                  << static_cast<int>(m_red) << ", "   //
                  << static_cast<int>(m_green) << ", " //
                  << static_cast<int>(m_blue) << ", "  //
                  << static_cast<int>(m_alpha) << ")"  //
                  << std::endl;                        //
    }

protected:
    static uint8_t multiplyChannel(uint8_t channel, double factor)
    {
        double temp = static_cast<double>(channel) * factor;

        if (temp > 255)
            temp = 255;

        if (temp < 0)
            temp = 0;

        return static_cast<uint8_t>(temp);
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
