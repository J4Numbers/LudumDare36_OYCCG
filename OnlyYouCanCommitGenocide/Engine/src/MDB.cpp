#include "../headers/MDB.hpp"

MDB::MDB()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        throw MDB_SDL_Exception();
    }
}

MDB::~MDB()
{
    SDL_Quit();
}

const char* MDB::get_last_error()
{
    return SDL_GetError();
}

MDB_Screen* MDB::request_screen(int w, int h, int flags)
{
    return new MDB_Screen(w, h, flags, SDL_RENDERER_ACCELERATED);
}
