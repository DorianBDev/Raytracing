#include "Material.h"

#include "Utils/Math.h"

Material::Material(double reflectivity, double refractivity, double transparency, double shininess)
    : m_reflectivity(reflectivity),
      m_refractivity(refractivity),
      m_transparency(transparency),
      m_shininess(shininess)
{
    if (m_reflectivity > 1.0)
        m_reflectivity = 1.0;

    if (m_reflectivity < 0.0)
        m_reflectivity = 0.0;

    if (m_transparency > 1.0)
        m_transparency = 1.0;

    if (m_transparency < 0.0)
        m_transparency = 0.0;

    if (m_shininess < 0.0)
        m_shininess = 0.0;
}

double Material::reflectivity() const
{
    return m_reflectivity;
}

double Material::refractivity() const
{
    return m_refractivity;
}

double Material::transparency() const
{
    return m_transparency;
}

double Material::shininess() const
{
    return m_shininess;
}

bool Material::isOpaque() const
{
    return areDoubleApproximatelyEqual(m_reflectivity, 0);
}

bool Material::isTransparent() const
{
    return !areDoubleApproximatelyEqual(m_transparency, 0);
}