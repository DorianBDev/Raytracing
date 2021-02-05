#ifndef H_RAYTRACING_SIZE_H
#define H_RAYTRACING_SIZE_H

#include <cstddef>

/**
 * @brief Class to use/set a size.
 */
struct Size
{
    /**
     * @brief Create a Size object.
     */
    Size() = default;

    /**
     * @brief Create a Size object.
     *
     * @param width  The width.
     * @param height The height.
     */
    Size(unsigned int width, unsigned int height) : m_width(width), m_height(height)
    {
    }

    /**
     * @brief Get the width.
     *
     * @return Returns the width value.
     */
    std::size_t width() const
    {
        return m_width;
    }

    /**
     * @brief Get the height.
     *
     * @return Returns the height value.
     */
    std::size_t height() const
    {
        return m_height;
    }

    /**
     * @brief Set the width value.
     *
     * @param width The new width value.
     */
    void setWidth(std::size_t width)
    {
        m_width = width;
    }

    /**
     * @brief Set the height value.
     *
     * @param height The new height value.
     */
    void setHeight(std::size_t height)
    {
        m_height = height;
    }

private:
    std::size_t m_width = 0;
    std::size_t m_height = 0;
};

#endif //H_RAYTRACING_SIZE_H
