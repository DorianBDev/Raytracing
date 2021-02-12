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
     * @param transparency Transparency of the material.
     * @param shininess    Shininess of the material.
     */
    Material(double reflectivity, double refractivity, double transparency, double shininess);
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
     * @brief Get the transparency of the material.
     *
     * @return Returns the transparency of the material.
     */
    double transparency() const;

    /**
     * @brief Get the shininess of the material.
     *
     * @return Returns the shininess of the material.
     */
    double shininess() const;

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
    double m_transparency;
    double m_shininess;
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
    inline Material metal(double reflectivity = 0.1)
    {
        return Material(reflectivity, 0.0, 0.0, 7.0);
    }

    /**
     * @brief Create a transparent material.
     *
     * @param reflectivity Reflectivity of the metal (default 0.8).
     *
     * @return Returns a metal material.
     */
    inline Material transparent(double reflectivity = 0.2, double refractivity = 1.20, double transparency = 0.8)
    {
        return Material(reflectivity, refractivity, transparency, 6.0);
    }
} // namespace Materials

#endif //H_RAYTRACING_MATERIAL_H
