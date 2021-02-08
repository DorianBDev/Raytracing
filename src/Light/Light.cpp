#include "Light.h"

Light::Light(double intensity, const Color& color) : m_intensity(intensity), m_color(color)
{
}

double Light::getIntensity() const
{
    return m_intensity;
}

Color Light::getColor() const
{
    return m_color;
}