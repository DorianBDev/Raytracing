#include "Light/Punctual.h"
#include "Objects/Sphere.h"
#include "Scene/Scene.h"

#include <iostream>

int main()
{
    Scene scene(std::make_shared<Camera>(Vector3(0, 0, 0), Vector3(0, 0, 1), Size(1920, 1080), 1));

    scene.addLight(std::make_shared<Punctual>(10, Vector3(5, 0, 10)))
            .addObject(std::make_shared<Sphere>(Vector3(0, 4, 15), Colors::blue(), 3))
            .addObject(std::make_shared<Sphere>(Vector3(0, 4, 8), Colors::white(), 1))
            .addObject(std::make_shared<Sphere>(Vector3(0, -4, 20), Colors::red(), 2))
            .addObject(std::make_shared<Sphere>(Vector3(5, -2, 30), Colors::green(), 2))
            .generate("out.png");

    return 0;
}