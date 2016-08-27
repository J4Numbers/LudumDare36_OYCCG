#ifndef MDB_COMMON_H
#define MDB_COMMON_H

#include <string>

#include "../../include/SDL2/SDL.h"

#include "MDB_Exceptions.hpp"

class MDB_Common
{

public:
    static void get_resource_path(char* & point, char* directory);

};

#endif