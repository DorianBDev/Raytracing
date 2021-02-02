#ifndef H_RAYTRACING_LIGHT_H
#define H_RAYTRACING_LIGHT_H

#include "Utils/Ray.h"

#include <optional>

/**
 * @class Light
 * @brief Class that manage the light.
 *
 * This class provides information about the light's intensity.
 *
 * @see Vector3, Matrix
 */
class Light
{
public:
    /**
     * @brief Constructor that initialize a light.
     *
     * @param intensity   The intensity of the light
     */
    explicit Light(double intensity);

    /**
     * @brief Method that return the intensity of the light.
     *
     * @return Returns the intensity of the light.
     */
    double getIntensity() const;

    /*
     * @brief Method that return if the secondary ray is enlightened.
     *
     * @param intersection The secondary ray
     *
     * @return Returns true if the ray is enlightened.
     */
    virtual bool isEnLight(Ray intersection) = 0;

    /**
     * @brief Method to get the origin of the light.
     *
     * @param intersection The secondary ray
     *
     * @return Returns the origin point of the light.
     */
    virtual std::optional<Vector3> getOrigin(Ray intersection) = 0;

    /**
     * @brief Method to get the direction of the light.
     *
     * @param intersection The secondary ray
     *
     * @return Returns the direction of the light.
     */
    virtual std::optional<Vector3> getDirection(Ray intersection) = 0;

private:
    /**
     * The intensity of the light.
     */
    double m_intensity;
};

#endif //H_RAYTRACING_LIGHT_H
