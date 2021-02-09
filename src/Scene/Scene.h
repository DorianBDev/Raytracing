#ifndef H_RAYTRACING_SCENE_H
#define H_RAYTRACING_SCENE_H

#include "Camera/Camera.h"
#include "Light/Light.h"
#include "Objects/Object.h"

#include <SFML/Graphics/Image.hpp>
#include <memory>
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
    std::shared_ptr<sf::Image> compute() const;

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
     * @return Returns the color (to add with the object color).
     */
    Color computeLight(const std::shared_ptr<Object>& intersectionObject,
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
                                           const Ray& primaryRay) const;

private:
    std::shared_ptr<Camera> m_camera;
    std::vector<std::shared_ptr<Light>> m_lights;
    std::vector<std::shared_ptr<Object>> m_objects;
};

#endif //H_RAYTRACING_SCENE_H
