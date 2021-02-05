#include "Camera.h"

Camera::Camera(const Vector3& coordinates, const Vector3& direction, const Size& resolution, double focal)
    : m_coordinates(coordinates),
      m_direction(direction),
      m_resolution(resolution),
      m_focal(focal)
{
    m_ratio = static_cast<double>(m_resolution.width()) / static_cast<double>(m_resolution.height());
}

void Camera::setCoordinates(const Vector3& coordinates)
{
    m_coordinates = coordinates;
}

void Camera::setDirection(const Vector3& direction)
{
    m_direction = direction;
}

void Camera::setFocal(double focal)
{
    m_focal = focal;
}

Size Camera::getResolution()
{
    return m_resolution;
}

Vector3 Camera::getCoordinates()
{
    return m_coordinates;
}

Vector3 Camera::getDirection()
{
    return m_direction;
}

double Camera::getFocal() const
{
    return m_focal;
}

double Camera::getRatio() const
{
    return m_ratio;
}