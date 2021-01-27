#include "Example/Example.hpp"

#define SDL_DISABLE_ANALYZE_MACROS
#include <SDL.h>
#include <iostream>

const int screenWidth = 800;
const int screenHeight = 600;

int main(int argc, char* argv[])
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
    }
    else
    {

        SDL_CreateWindow("SDL2 Demo",
                         SDL_WINDOWPOS_CENTERED,
                         SDL_WINDOWPOS_CENTERED,
                         screenWidth,
                         screenHeight,
                         SDL_WINDOW_SHOWN);

        SDL_Delay(2000);
    }

    return 0;
}