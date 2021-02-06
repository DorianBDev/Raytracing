#ifndef RAYTRACING_CAMERA_H
#define RAYTRACING_CAMERA_H

#include "Utils/Size.h"
#include "Utils/Vector3.h"

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
     * @param focal       Focal of the camera.
     */
    Camera(Vector3 coordinates, Vector3 direction, const Size& resolution, double focal);

    /**
     * @brief Method.
     *
     * This method change the coordinates of the camera.
     *
     * @param coordinates Coordinates for the camera.
     */
    void setCoordinates(const Vector3& coordinates);

    /**
     * @brief Method.
     *
     * This method change the direction of the camera.
     *
     * @param direction Direction for the camera.
     */
    void setDirection(const Vector3& direction);

    /**
     * @brief Method.
     *
     * This method change the camera's focal.
     *
     * @param focal Focal of the camera.
     */
    void setFocal(double focal);

    /**
     * @brief Get camera resolution.
     *
     * @return Returns the camera resolution.
     */
    Size getResolution();

    /**
     * @brief Method.
     *
     * This method return the coordinates of the camera.
     *
     * @return Returns the coordinates matrix.
     */
    Vector3 getCoordinates();

    /**
     * @brief Method.
     *
     * This method return the direction of the camera.
     *
     * @return Returns the direction matrix.
     */
    Vector3 getDirection();

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
    Vector3 m_coordinates;

    /**
     * The direction of the camera.
     */
    Vector3 m_direction;

    /**
     * The resolution of the camera.
     */
    Size m_resolution;

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
