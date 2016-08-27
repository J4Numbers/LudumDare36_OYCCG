#ifndef MDB_H
#define MDB_H

#include "../include/SDL2/SDL.h"

class MDB
{
public:
    MDB();

    int boot();
    const char* get_last_error();

    ~MDB();
};

#endif