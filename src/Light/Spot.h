#ifndef H_RAYTRACING_SPOT_H
#define H_RAYTRACING_SPOT_H

#include "Light.h"

constexpr double pi = 3.14;

/**
 * @class Punctual
 * @brief Class that manage the spot light.
 *
 * This class provides information about the spot light (direction, origins).
 *
 * @see Vector3, Matrix, Light
 */
class Spot : public Light
{
public:
    /**
     * @brief Constructor to initialize a spot light.
     *
     * @param intensity The intensity of the spot light
     * @param origin    The origin of the spot light
     * @param direction The direction of the spot light
     * @param angle     The angle of the spot light
     */
    Spot(double intensity, Vector3 origin, Vector3 direction, double angle);

    /*
     * @brief Method that return if the intersection is enlightened.
     *
     * @param intersection The secondary ray
     *
     * @return Returns true if the intersection is enlightened.
     */
    bool isEnLight(Ray intersection) override;

    /**
     * @brief Method to get the origin of the light.
     *
     * @param intersection The secondary ray
     *
     * @return Returns the origin point of the light.
     */
    std::optional<Vector3> getOrigin(Ray intersection) override;

    /**
     * @brief Method to get the direction of the light.
     *
     * @param intersection The secondary ray
     *
     * @return Returns the direction of the light.
     */
    std::optional<Vector3> getDirection(Ray intersection) override;

private:
    /**
     * The origin of the spot light.
     */
    Vector3 m_origin;

    /**
     * The direction of the spot light.
     */
    Vector3 m_direction;

    /**
     * The angle of the spot light.
     */
    double m_angle;
};

#endif //H_RAYTRACING_SPOT_H
