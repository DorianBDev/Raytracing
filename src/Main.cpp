#include "Scene/Scene.h"

#include <iostream>

int main(int argc, char** argv)
{
    if (argc != 2)
        return -1;

    try
    {
        Scene scene(Scene::camera(Vector3(0, 0, -15), Vector3(0, 0, 1), Size(1920, 1080), 1), 0.02);

        // Enable anti-aliasing
        scene.enableAntialiasing();

        // Load the lights and objects
        scene.loadScene(argv[1]);

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