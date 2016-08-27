#ifndef MDB_STRUCTS_H
#define MDB_STRUCTS_H

#include "../../include/SDL2/SDL.h"

struct MDB_Room
{
    uint32_t width;
    uint32_t height;

//Flags include such things as scroll direction and the speed of scroll
    uint32_t flags;
};

#endif