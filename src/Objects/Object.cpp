#include "Object.h"

Object::Object(const Vector3& coordinates, Color color) : m_coordinates(coordinates), m_color(color)
{
}

void Object::setCoordinates(const Vector3& coordinates)
{
    m_coordinates = coordinates;
}

void Object::setColor(Color color)
{
    m_color = color;
}

Vector3 Object::getCoordinates()
{
    return m_coordinates;
}

Color Object::getColor()
{
    return m_color;
}
