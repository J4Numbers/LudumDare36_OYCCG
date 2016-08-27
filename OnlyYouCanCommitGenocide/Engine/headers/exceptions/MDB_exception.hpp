#ifndef MDB_EXCEPTIONS_H
#define MDB_EXCEPTIONS_H

#include <exception>

class MDB_SDL_Exception : public std::exception
{
public:
    const char* what() const throw()
    { return "SDL Error\n"; };
};

#endif