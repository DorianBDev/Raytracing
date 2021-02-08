#ifndef H_RAYTRACING_DIRECTIONAL_H
#define H_RAYTRACING_DIRECTIONAL_H

#include "Light.h"

/**
 * @class Directional
 * @brief Class that manage the directional light.
 *
 * This class provides information about the directional light (direction, origins).
 *
 * @see Vector3, Matrix, Light
 */
class Directional : public Light
{
public:
    /**
     * @brief Constructor to initialize a directional light.
     *
     * @param intensity The intensity of the light
     * @param color     The color of the light
     * @param originA   The first origin of the light
     * @param originB   The last origin of the light
     * @param direction The direction of the light
     */
    Directional(double intensity, const Color& color, Vector3 originA, Vector3 originB, Vector3 direction);

    /*
     * @brief Method that return if the intersection is enlightened.
     *
     * @param origin The origin of the ray
     *
     * @return Returns true if the intersection is enlightened.
     */
    bool isEnLight(const Vector3& origin) const override;

    /**
     * @brief Method to get the origin of the light.
     *
     * @param origin The origin of the ray
     *
     * @return Returns the origin point of the light.
     */
    std::optional<Vector3> getOrigin(const Vector3& origin) const override;

    /**
     * @brief Method to get the direction of the light.
     *
     * @param origin The origin of the ray
     *
     * @return Returns the direction of the light.
     */
    std::optional<Vector3> getDirection(const Vector3& origin) const override;

private:
    /**
     * The first origin of the light.
     */
    Vector3 m_originA;

    /**
     * The last origin of the light.
     */
    Vector3 m_originB;

    /**
     * The direction of the light.
     */
    Vector3 m_direction;
};

#endif //H_RAYTRACING_DIRECTIONAL_H
