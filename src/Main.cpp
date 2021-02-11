#include "Light/Punctual.h"
#include "Objects/Plane.h"
#include "Objects/Sphere.h"
#include "Scene/Scene.h"

#include <iostream>

int main()
{
    try
    {
        Scene scene(Scene::camera(Vector3(0, 0, 0), Vector3(0, 0, 1), Size(1600, 900), 1));

        // Add light
        scene.addLight<Punctual>(2, Color(150, 150, 150), Vector3(10, 0, 10));

        // Add objects
        scene.addObject<Sphere>(Materials::metal(0.1), Colors::blue(), Vector3(-7, 0, 10), 2);
        scene.addObject<Sphere>(Materials::metal(0.1), Color(50, 50, 50), Vector3(-4, 0, 10), 1);
        scene.addObject<Sphere>(Materials::metal(0.1), Colors::red(), Vector3(0, -4, 20), 2);
        scene.addObject<Sphere>(Materials::metal(0.1), Colors::green(), Vector3(5, -2, 30), 2);
        scene.addObject<Plane>(Materials::metal(0.03), Color(10, 10, 10), Vector3(0, 5, 10), Vector3(0, -1, 0));

        scene.addObject<Sphere>(Materials::transparent(0, 1.1, 1), Colors::white(), Vector3(0, -2, 10), 2);
        //scene.addObject<Sphere>(Materials::transparent(0, 1.1, 0.9), Colors::white(), Vector3(0, 2, 15), 1);

        // Generate image
        scene.generate("out.png");

        // Show in window
        scene.show();
    }
    catch (std::exception& exception)
    {
        std::cout << exception.what() << std::endl;
    }

    return 0;
}