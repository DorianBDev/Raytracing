#include "Object.h"

#include <utility>

Object::Object(Color color) : m_color(color)
{
}

void Object::setColor(Color color)
{
    m_color = color;
}

Color Object::getColor()
{
    return m_color;
}
