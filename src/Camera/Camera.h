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
     * @param direction
     *     Direction of the camera.
     *
     * @param resolution
     *     Resolution of the camera.
     *
     * @param focale
     *     Focale of the camera.
     */
    Camera(const Matrix& coordinates, const Matrix& direction, const Matrix& resolution, double focale);

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
     * This method change the direction of the camera.
     *
     * @param direction
     *     Direction for the camera.
     */
    void setDirection(const Matrix& direction);

    /**
     * @brief Method.
     *
     * This method change the camera's focale.
     *
     * @param focale
     *     Focale of the camera.
     */
    void setFocale(double focale);

    /**
     * @brief Method.
     *
     * This method change the camera's ratio.
     *
     * @param ratio
     *     Ratio of the camera.
     */
    void setRatio(double ratio);

    /**
     * @brief Method.
     *
     * This method return the coordinates of the camera.
     */
    Matrix getCoordinates();

    /**
     * @brief Method.
     *
     * This method return the direction of the camera.
     */
    Matrix getDirection();

    /**
     * @brief Method.
     *
     * This method return the camera's focale.
     */
    double getFocale() const;

    /**
     * @brief Method.
     *
     * This method return the camera's ratio.
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
     * The focale of the camera.
     */
    double m_focale;

    /**
     * The ratio of the picture.
     */
    double m_ratio;
};

#endif //RAYTRACING_CAMERA_H
