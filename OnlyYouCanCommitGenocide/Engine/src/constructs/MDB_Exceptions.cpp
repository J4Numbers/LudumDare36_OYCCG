#include "../../headers/constructs/MDB_Exceptions.hpp"

const char* MDB_SDL_Exception::what() const throw()
{
    return "SDL Exception\n";
}

const char* MDB_IMG_Exception::what() const throw()
{
    return "SDL IMG Exception\n";
}