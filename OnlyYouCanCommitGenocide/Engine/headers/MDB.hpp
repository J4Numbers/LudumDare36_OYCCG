#ifndef MDB_H
#define MDB_H

#include <vector>

#include "../include/SDL2/SDL.h"
#include "../include/SDL2/SDL_image.h"

#include "constructs/MDB_Exceptions.hpp"
#include "constructs/MDB_Enums.hpp"
#include "constructs/MDB_Structs.hpp"

#include "constructs/MDB_Common.hpp"

#include "MDB_Screen.hpp"

class MDB
{
private:
    char * resource_path;
    bool quit;
    uint32_t start, current;

public:
    MDB();

    static const char* get_last_error();
    static const char* get_last_img_error();

    MDB_Screen* request_screen(int w, int h, int flags);

    char* return_res_path() const;

    void generate_file(char* file_name, std::vector<void*> file_data, uint32_t file_type);
    void read_file(char* file_name, uint32_t &type);

    void game_step();

    bool quitting();

    ~MDB();
};

#endif