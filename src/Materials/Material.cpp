#include "Material.h"

#include "Utils/Math.h"

Material::Material(double reflectivity, double refractivity)
    : m_reflectivity(reflectivity),
      m_refractivity(refractivity)
{
    if (m_reflectivity > 1.0)
        m_reflectivity = 1.0;

    if (m_reflectivity < 0.0)
        m_reflectivity = 0.0;

    if (m_refractivity > 1.0)
        m_refractivity = 1.0;

    if (m_refractivity < 0.0)
        m_refractivity = 0.0;
}

double Material::reflectivity() const
{
    return m_reflectivity;
}

double Material::refractivity() const
{
    return m_refractivity;
}

bool Material::isOpaque() const
{
    return areDoubleApproximatelyEqual(m_reflectivity, 0);
}

bool Material::isTransparent() const
{
    return !areDoubleApproximatelyEqual(m_refractivity, 0);
}