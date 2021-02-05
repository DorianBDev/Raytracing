#ifndef H_RAYTRACING_SCENE_H
#define H_RAYTRACING_SCENE_H

#include "Camera/Camera.h"
#include "Light/Light.h"
#include "Objects/Object.h"

#include <SFML/Graphics/Image.hpp>
#include <memory>
#include <vector>

/**
 * @brief Core class to store objects and primitives (like camera).
 */
class Scene
{
public:
    /**
     * @brief Create a scene with a camera.
     *
     * @param camera The camera used.
     */
    explicit Scene(std::shared_ptr<Camera> camera);
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
     * @brief Generate an image from the scene.
     *
     * @param light The light to add.
     *
     * @return Returns *this.
     */
    Scene& generate(const std::string& imagePath);

protected:
    /**
     * @brief Make the computation and get the corresponding image.
     *
     * @return Returns the generated image.
     */
    std::shared_ptr<sf::Image> compute();

    /**
     * @brief Get the pixel color from a ray.
     *
     * @param ray The ray to use to get the color.
     *
     * @return Returns the calculated color.
     */
    sf::Color getPixelColor(const Ray& ray);

private:
    std::shared_ptr<Camera> m_camera;
    std::vector<std::shared_ptr<Light>> m_lights;
    std::vector<std::shared_ptr<Object>> m_objects;
};

#endif //H_RAYTRACING_SCENE_H
