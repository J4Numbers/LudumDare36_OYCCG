#include <stdio.h>
#include <Windows.h>

#include "MDB.hpp"

int main(int argc, char** argv)
{
    try
    {
        MDB* m = new MDB();

        MDB_Screen* screen = m->request_screen(1280, 720, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);

        screen->set_screen_colour(255, 0, 0, 255);

        Sleep(5000);

        delete screen;

        delete m;
    }
    catch (MDB_SDL_Exception&)
    {
        fprintf(stdout, "Error loading SDL: %s\n", SDL_GetError());
        Sleep(5000);
    }

    return 0;
}
