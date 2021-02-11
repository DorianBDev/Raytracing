#ifndef H_RAYTRACING_COLOR_H
#define H_RAYTRACING_COLOR_H

#include "Vector3.h"

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
    }

    /**
     * @brief Create a new color object.
     *
     * @param red   The red channel value ([0;255]).
     * @param green The green channel value ([0;255]).
     * @param blue  The blue channel value ([0;255]).
     */
    constexpr Color(uint8_t red, uint8_t green, uint8_t blue) : m_red(red), m_green(green), m_blue(blue)
    {
    }

    /**
     * @brief Set the color.
     *
     * @param red   The red channel value ([0;255]).
     * @param green The green channel value ([0;255]).
     * @param blue  The blue channel value ([0;255]).
     */
    void setColor(uint8_t red, uint8_t green, uint8_t blue)
    {
        m_red = red;
        m_green = green;
        m_blue = blue;
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
     * @brief Scalar multiplication on each channel of the color.
     */
    Color operator*(double value) const
    {
        Color res;

        res.setColor(multiplyChannel(m_red, value), multiplyChannel(m_green, value), multiplyChannel(m_blue, value));

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

        clamp(red, green, blue);

        res.setColor(static_cast<uint8_t>(red), static_cast<uint8_t>(green), static_cast<uint8_t>(blue));

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

        return *this;
    }

    /**
     * @brief Convert the color to sf::Color.
     */
    sf::Color toSFMLColor() const
    {
        return sf::Color(m_red, m_green, m_blue, 255);
    }

    /**
     * @brief Print color.
     */
    void print() const
    {
        std::cout << "Color("                          //
                  << static_cast<int>(m_red) << ", "   //
                  << static_cast<int>(m_green) << ", " //
                  << static_cast<int>(m_blue) << ")"   //
                  << std::endl;
    }

    /**
     * @brief Multiplication operation.
     */
    Color operator*(const Color& color) const
    {
        int r = static_cast<int>(m_red) * static_cast<int>(color.m_red);
        int g = static_cast<int>(m_green) * static_cast<int>(color.m_green);
        int b = static_cast<int>(m_blue) * static_cast<int>(color.m_blue);

        clamp(r, g, b);

        return Color(static_cast<uint8_t>(r), static_cast<uint8_t>(g), static_cast<uint8_t>(b));
    }

    /**
     * @brief Division operation.
     */
    Color operator/(double value) const
    {
        double r = static_cast<double>(m_red) / value;
        double g = static_cast<double>(m_green) / value;
        double b = static_cast<double>(m_blue) / value;

        clamp(r, g, b);

        return Color(static_cast<uint8_t>(r), static_cast<uint8_t>(g), static_cast<uint8_t>(b));
    }

    /**
     * @brief Operator equal.
     */
    inline Color& operator=(const Vector3& vector)
    {
        double r = vector.x();
        double g = vector.y();
        double b = vector.z();

        clamp(r, g, b);

        m_red = static_cast<uint8_t>(r);
        m_green = static_cast<uint8_t>(g);
        m_blue = static_cast<uint8_t>(b);

        return *this;
    }

protected:
    inline static uint8_t multiplyChannel(uint8_t channel, double factor)
    {
        double temp = static_cast<double>(channel) * factor;

        if (temp > 255)
            temp = 255;

        if (temp < 0)
            temp = 0;

        return static_cast<uint8_t>(temp);
    }

    template<typename T>
    inline static void clamp(T& r, T& g, T& b)
    {
        if (r > 255)
            r = 255;

        if (g > 255)
            g = 255;

        if (b > 255)
            b = 255;

        if (r < 0)
            r = 0;

        if (g < 0)
            g = 0;

        if (b < 0)
            b = 0;
    }

private:
    uint8_t m_red = 0;
    uint8_t m_green = 0;
    uint8_t m_blue = 0;
};

inline Vector3 operator+(const Vector3& vector, const Color& color)
{
    return Vector3(vector.x() + color.red(), vector.y() + color.green(), vector.z() + color.blue());
}

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
