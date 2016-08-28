#ifndef MDB_INPUT_H
#define MDB_INPUT_H

//typedef struct TB_FloorList TB_FloorList;

#include <iostream>

#include "../include/SDL2/SDL.h"

#include "constructs/MDB_Structs.hpp"
#include "constructs/MDB_Common.hpp"
#include "constructs/MDB_Actors.hpp"
#include "constructs/MDB_System.hpp"

/**
* User input subsystem where we handle the user pressing buttons, then map
* those buttons to the functionality of the player character
*/
class MDB_Input : public MDB_System
{

private:
    MDB_Actor* player;

public:
    MDB_Input();
    virtual ~MDB_Input();

    virtual void manageEvent(SDL_Event e);

    void assignPlayer(MDB_Actor* p);

};

#endif