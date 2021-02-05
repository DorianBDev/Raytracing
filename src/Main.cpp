#include "Light/Punctual.h"
#include "Objects/Sphere.h"
#include "Scene/Scene.h"

#include <iostream>

int main()
{
    try
    {
        Scene scene(Scene::camera(Vector3(0, 0, 0), Vector3(0, 0, 1), Size(720, 480), 1));

        // Add light
        scene.addLight<Punctual>(10, Vector3(5, 0, 10));

        // Add objects
        scene.addObject<Sphere>(Vector3(0, 4, 15), Colors::blue(), 3);
        scene.addObject<Sphere>(Vector3(0, 4, 8), Colors::white(), 1);
        scene.addObject<Sphere>(Vector3(0, -4, 20), Colors::red(), 2);
        scene.addObject<Sphere>(Vector3(5, -2, 30), Colors::green(), 2);

        // Generate image
        scene.generate("out.png");
    }
    catch (std::exception& exception)
    {
        std::cout << exception.what() << std::endl;
    }

    return 0;
}