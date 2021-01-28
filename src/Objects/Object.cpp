#include "Object.h"

Object::Object(const Matrix& coordinates, Color color) : m_coordinates(coordinates), m_color(color)
{
}

void Object::setCoordinates(const Matrix& coordinates)
{
    m_coordinates = coordinates;
}

void Object::setColor(Color color)
{
    m_color = color;
}

Matrix Object::getCoordinates()
{
    return m_coordinates;
}

Color Object::getColor()
{
    return m_color;
}
