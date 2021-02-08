#include <Light/Punctual.h>
#include <Objects/Sphere.h>
#include <Scene/Scene.h>
#include <doctest.h>

TEST_CASE("Testing scene")
{
    Scene scene(Scene::camera(Vector3(0, 0, 0), Vector3(0, 0, 1), Size(256, 144), 1));

    // Create light
    CHECK_NOTHROW(scene.addLight<Punctual>(10, Colors::white(), Vector3(5, 0, 10)));

    // Create objects
    CHECK_NOTHROW(scene.addObject<Sphere>(Colors::blue(), Vector3(0, 4, 15), 3));
    CHECK_NOTHROW(scene.addObject<Sphere>(Colors::white(), Vector3(0, 4, 8), 1));
    CHECK_NOTHROW(scene.addObject<Sphere>(Colors::red(), Vector3(0, -4, 20), 2));
    CHECK_NOTHROW(scene.addObject<Sphere>(Colors::green(), Vector3(5, -2, 30), 2));

    // Generate output
    CHECK_NOTHROW(scene.generate("out.png"));
}