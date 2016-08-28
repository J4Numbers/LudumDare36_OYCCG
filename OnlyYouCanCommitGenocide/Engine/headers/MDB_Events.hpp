#ifndef MDB_EVENTS_H
#define MDB_EVENTS_H

#include "../include/SDL2/SDL.h"

#include "constructs/MDB_Structs.hpp"
#include "constructs/MDB_Common.hpp"

#include "MDB_Audio.hpp"
#include "MDB_Screen.hpp"
#include "MDB_Inputs.hpp"

/**
 * The events class deals with the polling event loop. Whenever something
 * happens to the game itself, we can delegate the functionality to another
 * subsystem in order to defer functionality requirements and, well, definition
 */
class MDB_Events
{

public:
    /**
     * We require the floors for events as we are going to be constantly polling
     * and queueing events onto other floor's queues as we find them
     */
    MDB_Events();
    ~MDB_Events();

    /**
     * Perform a poll loop
     *
     * @return If we return -1, we want to exit the program
     */
    int pollEvents();

    /**
     * This was originally planned to be a threaded subsystem, but that didn't
     * work for the reason that polling can't happen within a thread for
     * whatever reason (I'm not actually entirely sure)
     *
     * @param  ptr Pointer to ourself
     * @return     0 on completion
     */
    static int thread_handler(void* ptr);

    /**
     * If this is ever true, we know to break the poll loop and flee
     */
    bool quit;

};

#endif