#ifndef RAYTRACING_CAMERA_H
#define RAYTRACING_CAMERA_H

#include "Utils/Matrix.h"

/**
 * @class Camera
 * @brief Class that manage the camera.
 *
 * Class that manage the camera.
 * Manage the coordinates, the angle and the scope of the camera.
 *
 * @see Matrix
 */
class Camera
{

public:
    /**
     * @brief Constructor.
     *
     * This constructor initialize the camera object.
     *
     * @param coordinates
     *     Coordinates for the camera.
     *
     * @param angle
     *     View's angle of the camera.
     *
     * @param scope
     *     Scope of the camera.
     */
    Camera(const Matrix& coordinates, double angle, double scope);


    /**
     * @brief Method.
     *
     * This method change the coordinates of the camera.
     *
     * @param coordinates
     *     Coordinates for the camera.
     */
    void setCoordinates(const Matrix& coordinates);

    /**
     * @brief Method.
     *
     * This method change the camera's angle.
     *
     * @param angle
     *     View's angle of the camera.
     */
    void setAngle(double angle);

    /**
     * @brief Method.
     *
     * This method change the camera's scope.
     *
     * @param scope
     *     Scope of the camera.
     */
    void setScope(double scope);

private:
    /**
     * The coordinates of the camera.
     */
    Matrix m_coordinates;

    /**
     * The view's angle of the camera.
     */
    double m_angle;

    /**
     * The scope of the camera.
     */
    double m_scope;
};


#endif //RAYTRACING_CAMERA_H
