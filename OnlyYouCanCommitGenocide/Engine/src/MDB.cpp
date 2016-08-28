#include "../headers/MDB.hpp"

MDB::MDB() : quit(false)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        throw MDB_SDL_Exception();
    }

    start = SDL_GetTicks();
    current = SDL_GetTicks();

    if (IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG)
    {
        throw MDB_IMG_Exception();
    }

    MDB_Common::get_resource_path(resource_path, "OnlyYouCanCommitGenocide");
}

MDB::~MDB()
{
    SDL_Quit();
}

const char* MDB::get_last_error()
{
    return SDL_GetError();
}

const char* MDB::get_last_img_error()
{
    return IMG_GetError();
}

char* MDB::return_res_path() const
{
    return resource_path;
}


MDB_Screen* MDB::request_screen(int w, int h, int flags)
{
    return new MDB_Screen(w, h, flags, SDL_RENDERER_ACCELERATED);
}

bool MDB::quitting()
{
    return quit;
}

void MDB::game_step()
{
    current = SDL_GetTicks();

    if (current - start > 10000)
    {
        quit = true;
    }
}
