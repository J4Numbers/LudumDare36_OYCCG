#ifndef MDB_LEVELS_H
#define MDB_LEVELS_H

#include <vector>

#include "../include/SDL2/SDL.h"

#include "constructs/MDB_Enums.hpp"

#include "constructs/MDB_Actors.hpp"

/**
* A stage it the actual level data for any one level that is being rendered
* and played, although at this point, it's mostly just a struct which contains
* all the objects within the level that are going to be rendered.
*/
class MDB_Levels
{
private:
    int objCount;
    //TB_Object** stageObjs;
    std::vector<MDB_Shape*> stageObjs;

public:
    MDB_Levels(int objCount, MDB_Actor** stageObjs);
    MDB_Levels(std::vector<MDB_Actor*> stageObjs);
    MDB_Levels();
    ~MDB_Levels();

    std::vector<MDB_Actor*> getObjects();

};

#endif