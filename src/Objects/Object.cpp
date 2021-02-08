#include "Object.h"

#include <utility>

Object::Object(const Color& color) : m_color(color)
{
}

void Object::setColor(const Color& color)
{
    m_color = color;
}

Color Object::getColor()
{
    return m_color;
}
