#include "../headers/MDB.hpp"

MDB::MDB()
{}

MDB::~MDB()
{}

int MDB::boot()
{
    return SDL_Init(SDL_INIT_EVERYTHING);
}

const char* MDB::get_last_error()
{
    return SDL_GetError();
}

MDB_Screen* MDB::request_screen(int w, int h, int flags)
{
    return new MDB_Screen(w, h, flags);
}
