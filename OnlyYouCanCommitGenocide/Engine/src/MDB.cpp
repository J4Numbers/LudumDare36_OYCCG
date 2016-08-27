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

