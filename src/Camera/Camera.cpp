#include "Camera.h"


Camera::Camera(const Matrix& coordinates, double angle, double scope)
    : m_coordinates(coordinates),
      m_angle(angle),
      m_scope(scope)
{
}


void Camera::setCoordinates(const Matrix& coordinates)
{
    m_coordinates = coordinates;
}


void Camera::setAngle(double angle)
{
    m_angle = angle;
}

void Camera::setScope(double scope)
{
    m_scope = scope;
}