#include "Object.h"

#include <utility>

Object::Object(Material material, const Color& color) : m_color(color), m_material(material)
{
}

void Object::setColor(const Color& color)
{
    m_color = color;
}

Color Object::getColor() const
{
    return m_color;
}

Material Object::getMaterial() const
{
    return m_material;
}
