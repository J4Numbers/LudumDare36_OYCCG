#ifndef MDB_H
#define MDB_H

#include "../include/SDL2/SDL.h"

#include "constructs/MDB_Exceptions.hpp"
#include "constructs/MDB_Enums.hpp"
#include "constructs/MDB_Structs.hpp"

#include "constructs/MDB_Common.hpp"

#include "MDB_Screen.hpp"

class MDB
{
private:
    char * resource_path;

public:
    MDB();

    static const char* get_last_error();

    MDB_Screen* request_screen(int w, int h, int flags);

    char* return_res_path() const;

    ~MDB();
};

#endif