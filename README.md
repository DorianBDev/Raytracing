[![Raytracing image](etc/banner.png)]()

# Raytracing

This project contains:

- Basic raytracing,
- Multithreading
- Unit testing,
- Lights (directional, punctual, spot),
- Colorized lights,
- Objects (sphere, plane, triangle),
- Reflection,
- Refraction,
- SFML Window,
- Continuous integration (see Github Actions),
- Transparency,
- Recursivity,
- Movable camera,
- SSAA anti-aliasing,
- OBJ loading,
- Config file for objects in parameters,
- Modern c++ (c++17).

## Multithreading

To enable multithreading, please go to the "Config.h" file.

## Template

This project uses the [cpp-template](https://github.com/DorianBDev/cpp-template) of [Dorian Bachelot](https://github.com/DorianBDev).

# Build

## Dependencies

- CMake 3.12.0 or newer,
- Conan,
- Python (optional).

## Quick start

Firstly, clone this repository (help [here](https://docs.github.com/en/github/creating-cloning-and-archiving-repositories/cloning-a-repository)).

### For Linux (debian-like)

Install dependencies:
```console
> sudo apt-get install cmake g++ python
> sudo pip install conan
```
Build (in the 'build' folder, for example):
```console
> cmake ..
> make
```
Binaries are in the 'build/bin' folder.

### For Windows

Install dependencies:
- CMake: https://cmake.org/download/,
- A compiler (for example MSVC): https://visualstudio.microsoft.com/,
- Conan: https://conan.io/,
- Python: https://www.python.org/ (optional).

Build (in the 'build' folder, for example):
```console
> cmake ..
> cmake --build .
```
Binaries are in the 'build/bin' folder.

### For MacOS

Install dependencies (we will use [Homebrew](https://brew.sh) here) :
- XCode: https://apps.apple.com/app/xcode/id497799835

```console
> brew install python
> brew install conan
```

Build (in the 'build' folder, for example):
```console
> cmake ..
> cmake --build .
```
Binaries are in the 'build/bin' folder in the bundle ".app" format.

### File format

To initialize the objects and lights, you need to specify the config file path. The '|' are replaced by blank space in the file.

The file can contains these objects and lights :
- Color definition    : defined name | undefined r g b
- Vector definition   : x y z
- Structure definition : metal reflectivity | transparent reflectivity refractivity transparency


- Punctual format    : Name | Intensity | Color | Vector Coordinates
- Spot Format        : Name | Intensity | Color | Vector Coordinates | Vector direction | Angle
- Directional Format : Name | Structure type | Color | Vector Coordinates A | Vector Coordinates B | Vector Direction


- Shere Format : Name | Structure type | Color | Vector Coordinates | Radius
- Plane Format : Name | Structure type | Color | Vector Coordinates | Vector Normal
- Model Format : Name | Structure type | Color | File model path | Vector Coordinates | Vector Angle | Scale

# License

MIT license. See LICENSE.TXT for details.
