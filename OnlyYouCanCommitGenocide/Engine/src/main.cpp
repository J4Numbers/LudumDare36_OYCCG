#include <stdio.h>

#include <Windows.h>

#include "../include/SDL2/SDL.h"

int main(int argc, char** argv)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
    {
        fprintf(stdout, "Error: %s\n", SDL_GetError());
    }

    Sleep(5000);

    return 0;
}
