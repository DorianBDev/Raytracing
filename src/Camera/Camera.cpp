#include "Camera.h"

Camera::Camera(const Matrix& coordinates, const Matrix& direction, const Matrix& resolution, double focale)
    : m_coordinates(coordinates),
      m_direction(direction),
      m_resolution(resolution),
      m_focale(focale)
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

void Camera::setFocale(double focale)
{
    m_focale = focale;
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

double Camera::getFocale() const
{
    return m_focale;
}

double Camera::getRatio() const
{
    return m_ratio;
}