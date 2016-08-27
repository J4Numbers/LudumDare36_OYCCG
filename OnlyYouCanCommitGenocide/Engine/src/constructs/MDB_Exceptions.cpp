#include "../../headers/constructs/MDB_Exceptions.hpp"

const char* MDB_SDL_Exception::what() const throw()
{
    return "SDL Exception\n";
}
