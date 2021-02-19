#ifndef H_RAYTRACING_SCENE_H
#define H_RAYTRACING_SCENE_H

#include "Camera/Camera.h"
#include "Light/Light.h"
#include "Objects/Object.h"

#include <SFML/Graphics/Image.hpp>
#include <fstream>
#include <memory>
#include <regex>
#include <sstream>
#include <string>
#include <vector>

using IntersectionResult = std::optional<std::pair<std::shared_ptr<Object>, Vector3>>;

/**
 * @brief Core class to store objects and primitives (like camera).
 */
class Scene
{
public:
    /**
     * @brief Create a scene with a camera.
     *
     * @param camera       The camera used.
     * @param ambientLight The ambient light of the scene (coefficient in [0,1]).
     */
    explicit Scene(std::shared_ptr<Camera> camera, double ambientLight = 0.2);
    ~Scene() = default;

    /**
     * @brief Add a light to the scene.
     *
     * @tparam T The type to create.
     *
     * @param args Args to use to create the light T.
     *
     * @return Returns *this.
     */
    template<typename T, typename... Args>
    Scene& addLight(Args... args)
    {
        m_lights.push_back(std::make_shared<T>(args...));

        return *this;
    }

    /**
     * @brief Add an object to the scene.
     *
     * @tparam T The type to create.
     *
     * @param args Args to use to create the object T.
     *
     * @return Returns *this.
     */
    template<typename T, typename... Args>
    Scene& addObject(Args... args)
    {
        m_objects.push_back(std::make_shared<T>(args...));

        return *this;
    }

    /**
     * @brief Create a camera for the scene.
     *
     * @param args Args to use to create the camera.
     *
     * @return Returns *this.
     */
    template<typename... Args>
    static std::shared_ptr<Camera> camera(Args... args)
    {
        return std::make_shared<Camera>(args...);
    }

    /**
     * @brief Load the lights and objects from a config file.
     *
     * @param path The path of the config file.
     */
    void loadScene(const std::string& path);

    /**
     * @brief Split a material element of the config file.
     *
     * @param stream The stream of the material.
     *
     * @return Returns the material associated in the file.
     */
    static Material splitMaterial(std::stringstream& stream);

    /**
     * @brief Split a vector3 element of the config file.
     *
     * @param stream The stream of the vector3.
     *
     * @return Returns the vector3 associated in the file.
     */
    static Vector3 splitVector3(std::stringstream& stream);

    /**
     * @brief Split the color element of the config file.
     *
     * @param stream The stream of the color.
     *
     * @return Returns the color associated in the file.
     */
    static Color splitColor(std::stringstream& stream);

    /**
     * @brief Get the defined color associated.
     *
     * @param name The name of the color.
     *
     * @return Returns the color defined.
     */
    static Color getColor(const std::string& name);

    /**
     * @brief Generate an image from the scene.
     *
     * @param light       The light to add.
     * @param recursivity Recursivity used for reflection and refraction computation (default 1).
     *
     * @return Returns *this.
     */
    Scene& generate(const std::string& imagePath, unsigned int recursivity = 1);

    /**
     * @brief Show last generated image (if empty, will generate one).
     *
     * @return Returns *this.
     */
    Scene& show();

    /**
     * @brief Enable anti-aliasing.
     *
     * @param antialiasingSampling Anti-aliasing sampling value (4, 8 or 16).
     */
    void enableAntialiasing(std::size_t antialiasingSampling = 4);

    /**
     * @brief Disable anti-aliasing.
     */
    void disableAntialiasing();

protected:
    /**
     * @brief Make the computation and get the corresponding image.
     *
     * @param recursivity Recursivity used for reflection and refraction computation.
     *
     * @return Returns the generated image.
     */
    std::shared_ptr<sf::Image> compute(unsigned int recursivity = 1) const;

    /**
     * @brief Get the intersected object and intersection point by a primary ray.
     *
     * @param ray The primary ray to use.
     *
     * @return Returns the intersected object and point.
     */
    IntersectionResult getIntersectedObject(const Ray& ray) const;

    /**
     * @brief Compute the light impact on the object color.
     *
     * @param intersectionObject The intersected object.
     * @param intersectionPoint  The intersection point.
     * @param primaryRay         The primary ray.
     *
     * @return Returns the combined intensity and colors of all lights.
     */
    std::pair<double, Color> computeLight(const std::shared_ptr<Object>& intersectionObject,
                                          const Vector3& intersectionPoint,
                                          const Ray& primaryRay) const;

    /**
     * @brief Check if the intersection point is illuminated.
     *
     * @warning Need to have the intersection point as the secondary ray origin.
     *
     * @param secondaryRay The secondary ray to use. See the warning above.
     * @param lightOrigin  The light origin.
     *
     * @return Returns true if the intersection point is illuminated, false otherwise.
     */
    bool isIlluminated(const Ray& secondaryRay, const Vector3& lightOrigin) const;

    /**
     * @brief Compute the reflection impact on the object color.
     *
     * @param intersectionObject The intersected object.
     * @param intersectionPoint  The intersection point.
     * @param primaryRay         The primary ray.
     *
     * @return Returns the color (to add with the object color).
     */
    std::optional<Color> computeReflection(const std::shared_ptr<Object>& intersectionObject,
                                           const Vector3& intersectionPoint,
                                           const Ray& primaryRay,
                                           unsigned int recursivity = 0) const;

    /**
     * @brief Compute the refraction impact on the object color.
     *
     * @param intersectionObject The intersected object.
     * @param intersectionPoint  The intersection point.
     * @param primaryRay         The primary ray.
     *
     * @return Returns the color (to add with the object color).
     */
    std::optional<Color> computeRefraction(const std::shared_ptr<Object>& intersectionObject,
                                           const Vector3& intersectionPoint,
                                           const Ray& primaryRay,
                                           unsigned int recursivity = 0) const;

    /**
     * @brief Function (with recursivity) to get the color of an intersected object.
     *
     * @param intersectionObject The intersection object.
     * @param intersectionPoint  The intersection point.
     * @param primaryRay         The primary ray.
     * @param recursivity        The level of recursivity (default 0 = no recursivity).
     *
     * @return Returns the color of the intersected object.
     */
    Color getColor(const std::shared_ptr<Object>& intersectionObject,
                   const Vector3& intersectionPoint,
                   const Ray& primaryRay,
                   unsigned int recursivity = 0) const;

private:
    std::shared_ptr<Camera> m_camera;
    std::vector<std::shared_ptr<Light>> m_lights;
    std::vector<std::shared_ptr<Object>> m_objects;
    Color m_backgroundColor = Colors::black();
    std::string m_lastSavedImage;
    std::size_t m_antialiasingSampling = 0;
    double m_ambientLight;
};

#endif //H_RAYTRACING_SCENE_H
