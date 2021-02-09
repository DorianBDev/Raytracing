#ifndef H_RAYTRACING_MATERIAL_H
#define H_RAYTRACING_MATERIAL_H

/**
 * @class Material
 * @brief Base material class.
 */
class Material
{
public:
    /**
     * @brief Create a Material object.
     *
     * @param reflectivity Reflectivity of the material.
     * @param refractivity Refractivity of the material.
     */
    Material(double reflectivity, double refractivity);
    ~Material() = default;

    /**
     * @brief Get the reflectivity of the material.
     *
     * @return Returns the reflectivity of the material.
     */
    double reflectivity() const;

    /**
     * @brief Get the refractivity of the material.
     *
     * @return Returns the refractivity of the material.
     */
    double refractivity() const;

    /**
     * @brief Know if the material is opaque.
     *
     * @return Returns true if the material is opaque, false otherwise.
     */
    bool isOpaque() const;

    /**
     * @brief Know if the material is transparent.
     *
     * @return Returns true if the material is transparent, false otherwise.
     */
    bool isTransparent() const;

private:
    double m_reflectivity;
    double m_refractivity;
};

namespace Materials
{
    /**
     * @brief Create a metal material.
     *
     * @param reflectivity Reflectivity of the metal (default 0.8).
     *
     * @return Returns a metal material.
     */
    inline Material metal(double reflectivity = 0.8)
    {
        return Material(reflectivity, 0.0);
    }
} // namespace Materials

#endif //H_RAYTRACING_MATERIAL_H
