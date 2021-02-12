#include "Light/Punctual.h"
#include "Objects/Model.h"
#include "Objects/Plane.h"
#include "Objects/Sphere.h"
#include "Scene/Scene.h"

#include <iostream>

int main()
{
    try
    {
        Scene scene(Scene::camera(Vector3(0, 0, -15), Vector3(0, 0, 1), Size(1920, 1080), 1), 0.02);

        // Enable anti-aliasing
        scene.enableAntialiasing();

        // Add light
        scene.addLight<Punctual>(8, Color(150, 150, 150), Vector3(10, -5, 10));
        scene.addLight<Punctual>(4, Color(255, 0, 0), Vector3(0, 0, 4));

        // Add objects
        scene.addObject<Sphere>(Materials::metal(0.1), Colors::red(), Vector3(0, -4, 20), 2);
        scene.addObject<Sphere>(Materials::metal(0.1), Colors::green(), Vector3(5, -2, 30), 2);
        scene.addObject<Sphere>(Materials::metal(0.1), Colors::blue(), Vector3(-7, 0, 10), 2);
        scene.addObject<Sphere>(Materials::metal(0.1), Color(50, 50, 50), Vector3(-4, 0, 10), 1);
        scene.addObject<Sphere>(Materials::transparent(0.5, 1.1, 1), Colors::white(), Vector3(0, -2, 6), 1);
        scene.addObject<Plane>(Materials::metal(0.03), Color(10, 10, 10), Vector3(0, 5, 10), Vector3(0, -0.5, 0));

        // Add .obj
        scene.addObject<Model>(Materials::metal(0.4),
                               Color(5, 5, 5),
                               "res/Object/cube.obj",
                               Vector3(-1, 3, 8),
                               Vector3(10, 10, 10),
                               0.3);

        // Generate image
        scene.generate("out.png", 1);

        // Show in window
        scene.show();
    }
    catch (std::exception& exception)
    {
        std::cout << exception.what() << std::endl;
    }

    return 0;
}