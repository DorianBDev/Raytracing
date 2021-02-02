#include "Light.h"

Light::Light(double intensity) : m_intensity(intensity)
{
}

double Light::getIntensity() const
{
    return m_intensity;
}