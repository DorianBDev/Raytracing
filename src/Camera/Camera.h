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
     * @param coordinates Coordinates for the camera.
     * @param direction   Direction of the camera.
     * @param resolution  Resolution of the camera.
     * @param focal      Focal of the camera.
     */
    Camera(const Matrix& coordinates, const Matrix& direction, const Matrix& resolution, double focal);

    /**
     * @brief Method.
     *
     * This method change the coordinates of the camera.
     *
     * @param coordinates Coordinates for the camera.
     */
    void setCoordinates(const Matrix& coordinates);

    /**
     * @brief Method.
     *
     * This method change the direction of the camera.
     *
     * @param direction Direction for the camera.
     */
    void setDirection(const Matrix& direction);

    /**
     * @brief Method.
     *
     * This method change the camera's focal.
     *
     * @param focal Focal of the camera.
     */
    void setFocal(double focal);

    /**
     * @brief Method.
     *
     * This method change the camera's ratio.
     *
     * @param ratio Ratio of the camera.
     */
    void setRatio(double ratio);

    /**
     * @brief Method.
     *
     * This method return the coordinates of the camera.
     *
     * @return Returns the coordinates matrix.
     */
    Matrix getCoordinates();

    /**
     * @brief Method.
     *
     * This method return the direction of the camera.
     *
     * @return Returns the direction matrix.
     */
    Matrix getDirection();

    /**
     * @brief Method.
     *
     * This method return the camera's focal.
     *
     * @param Returns the focal length.
     */
    double getFocal() const;

    /**
     * @brief Method.
     *
     * This method return the camera's ratio.
     *
     * @return Returns the picture's ratio.
     */
    double getRatio() const;

private:
    /**
     * The coordinates of the camera.
     */
    Matrix m_coordinates;

    /**
     * The direction of the camera.
     */
    Matrix m_direction;

    /**
     * The resolution of the camera.
     */
    Matrix m_resolution;

    /**
     * The focal of the camera.
     */
    double m_focal;

    /**
     * The ratio of the picture.
     */
    double m_ratio;
};

#endif //RAYTRACING_CAMERA_H
