#ifndef MDB_H
#define MDB_H

#include "../include/SDL2/SDL.h"

#include "MDB_Screen.hpp"

class MDB
{
public:
    MDB();

    int boot();
    const char* get_last_error();

    MDB_Screen* request_screen(int w, int h, int flags);

    ~MDB();
};

#endif