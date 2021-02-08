#include "Light/Punctual.h"
#include "Objects/Sphere.h"
#include "Scene/Scene.h"

#include <iostream>

int main()
{
    try
    {
        Scene scene(Scene::camera(Vector3(0, 0, 0), Vector3(0, 0, 1), Size(1920, 1080), 1));

        // Add light
        scene.addLight<Punctual>(2.5, Color(150, 150, 150), Vector3(10, 0, 10));

        // Add objects
        scene.addObject<Sphere>(Colors::blue(), Vector3(-7, 0, 10), 2);
        scene.addObject<Sphere>(Color(50, 50, 50), Vector3(-4, 0, 10), 1);
        scene.addObject<Sphere>(Colors::red(), Vector3(0, -4, 20), 2);
        scene.addObject<Sphere>(Colors::green(), Vector3(5, -2, 30), 2);

        // Generate image
        scene.generate("out.png");
    }
    catch (std::exception& exception)
    {
        std::cout << exception.what() << std::endl;
    }

    return 0;
}