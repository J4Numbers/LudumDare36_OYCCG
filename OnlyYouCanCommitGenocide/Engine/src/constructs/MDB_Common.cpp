#include "../../headers/constructs/MDB_Common.hpp"

void MDB_Common::get_resource_path(char* & point, char* directory)
{
#ifdef _WIN32
    const char PATH_SEP = '\\';

#else
    const char PATH_SEP = '/';
#endif

    if (point == nullptr)
    {
        std::string path;
        char *base_path = SDL_GetBasePath();
        if (base_path)
        {
            path = base_path;
            SDL_free(base_path);
        }
        else
        {
            throw MDB_SDL_Exception();
        }

        size_t pos = path.rfind(directory);
        path = path.substr(0, pos) + directory + PATH_SEP + "res" + PATH_SEP + '\0';
        pos = path.rfind(PATH_SEP)+1;

        point = new char[pos];
        memcpy_s(point, pos, path.c_str(), pos);
        point[pos] = '\0';

    }
    
}
