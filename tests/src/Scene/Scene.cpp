#include <Light/Punctual.h>
#include <Objects/Sphere.h>
#include <Scene/Scene.h>
#include <doctest.h>

TEST_CASE("Testing scene")
{
    Scene scene(Scene::camera(Vector3(0, 0, 0), Vector3(0, 0, 1), Size(256, 144), 1));

    // Create light
    CHECK_NOTHROW(scene.addLight<Punctual>(10, Vector3(5, 0, 10)));

    // Create objects
    CHECK_NOTHROW(scene.addObject<Sphere>(Vector3(0, 4, 15), Colors::blue(), 3));
    CHECK_NOTHROW(scene.addObject<Sphere>(Vector3(0, 4, 8), Colors::white(), 1));
    CHECK_NOTHROW(scene.addObject<Sphere>(Vector3(0, -4, 20), Colors::red(), 2));
    CHECK_NOTHROW(scene.addObject<Sphere>(Vector3(5, -2, 30), Colors::green(), 2));

    // Generate output
    CHECK_NOTHROW(scene.generate("out.png"));
}