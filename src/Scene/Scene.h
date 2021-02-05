#ifndef H_RAYTRACING_SCENE_H
#define H_RAYTRACING_SCENE_H

#include "Camera/Camera.h"
#include "Light/Light.h"
#include "Objects/Object.h"

#include <SFML/Graphics/Image.hpp>
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
     * @param light The light to add.
     *
     * @return Returns *this.
     */
    Scene& addLight(const std::shared_ptr<Light>& light);

    /**
     * @brief Add an object to the scene.
     *
     * @param object The object to add.
     *
     * @return Returns *this.
     */
    Scene& addObject(const std::shared_ptr<Object>& object);

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
