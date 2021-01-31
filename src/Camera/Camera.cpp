#include "Camera.h"

Camera::Camera(const Matrix& coordinates, const Matrix& direction, const Matrix& resolution, double focal)
    : m_coordinates(coordinates),
      m_direction(direction),
      m_resolution(resolution),
      m_focal(focal)
{
    m_ratio = m_resolution.value(0, 0) / m_resolution.value(1, 0);
}

void Camera::setCoordinates(const Matrix& coordinates)
{
    m_coordinates = coordinates;
}

void Camera::setDirection(const Matrix& direction)
{
    m_direction = direction;
}

void Camera::setFocal(double focal)
{
    m_focal = focal;
}

void Camera::setRatio(double ratio)
{
    m_ratio = ratio;
}

Matrix Camera::getCoordinates()
{
    return m_coordinates;
}

Matrix Camera::getDirection()
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