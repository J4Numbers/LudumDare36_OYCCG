#ifndef TB_AUDIO_H
#define TB_AUDIO_H

//typedef struct TB_FloorList TB_FloorList;

#include "../include/SDL2/SDL.h"
//#include "../include/SDL2/SDL_mixer.h"

#include "constructs/MDB_Structs.hpp"
#include "constructs/MDB_Common.hpp"
#include "constructs/MDB_System.hpp"

/**
* Audio Subsystem (currently unfinished), which allows for the playing of
* sounds and music to the player within the game. The ideal state of this is
* that another method 'playSound' will be added which can be called from the
* actors and the levels with a slug pointing towards a sound effect that is
* subsequently played.
*
* This should also be the same with music, though there will probably be more
* options in order to pause, switch, and generally mess with the music.
*/
class MDB_Audio : public MDB_System
{

private:
    /**
    * The music which is currently being played to the player
    */
    // Mix_Music* m;

public:
    /**
    * Create our new subsystem
    */
    MDB_Audio();
    virtual ~MDB_Audio();

    /**
    * As per TB_System sub-class definition, we must manage our own events
    * that we are passed (which, at this point, is no events funnily enough)
    *
    * @param e The event we're being asked to handle
    */
    virtual void manageEvent(SDL_Event e);

};

#endif