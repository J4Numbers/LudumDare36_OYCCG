#ifndef MDB_SYSTEM_H
#define MDB_SYSTEM_H

//typedef struct TB_FloorList TB_FloorList;

#include "../../include/SDL2/SDL.h"

/**
* Parent class of all subsystems which has functionality for handling polling
* queues for events. Every subclass of System has an event queue which they
* handle on their own, but we provide a bit of the heavy lifting for adding
* stuff within this part.
*/
class MDB_System
{
public:
    MDB_System();

    virtual ~MDB_System();

    void addEvent(SDL_Event e);

    void pollEvent();

    virtual void manageEvent(SDL_Event e) = 0;

protected:
    SDL_Event* eventBuffer;
    int bufferLength;
    int bufferStart;
};

#endif