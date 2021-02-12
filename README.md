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
- Modern c++ (c++17).

## Multithreading

To enable multithreading, please go to the "Config.h" file.

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

# License

MIT license. See LICENSE.TXT for details.
