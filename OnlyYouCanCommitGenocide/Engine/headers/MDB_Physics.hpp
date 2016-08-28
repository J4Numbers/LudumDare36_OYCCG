#ifndef TB_PHYSICS_H
#define TB_PHYSICS_H

#include <iostream>
#include <vector>
#include <algorithm>

#include "../include/SDL2/SDL.h"

#include "constructs/MDB_Structs.hpp"
#include "constructs/MDB_Enums.hpp"
#include "constructs/MDB_Common.hpp"
#include "constructs/MDB_Actors.hpp"

/*
At this point, it seems like a good idea to stipulate what exactly we need for any object
that we want to have physics act on at some point in time. This is mostly according to the
SUVAT equations for which we will define two instances of deriving the distance travelled
over time and all that jazz.

We will look at the Symplectic Euler Integration, where we derive the distance travelled
immediately after finding out the velocity at this point in time. For this integration
method, we require the following information to be provided:
- Current velocity (vector2)
- Current acceleration (vector2)
- Difference in time since last update (float)
- Displacement within the previous frame (vector2)

All of these come together to make the two equations:
v(x+1) = v(x) + (a(x) * t)
s(x+1) = s(x) + (v(x+1) * t)

We will also look into making Verlet Integration, which allows for backtracking whilst being
just as efficient (though slightly less so as SEI). The requirements for this integration are
similar to SEI, however they are altered so that the current velocity is never needed:
- Current acceleration (vector2)
- Difference in time since the last update (float)
- Displacement within the previous frame (vector2)
- Displacement within the frame prior to the previous frame (vector2)

Which comes together to create the equation:
s(x+1) = s(x) + (s(x) - s(x-1)) + (a(x) * t^2)

The Runge-Kutta method may also be a possibility, however it requires some thinking about in
order to even start creating the algorithm that's required to work stuff out. Ergo, screw that
for the time being - I'll probably look into creating it if I have the time as it's apparently
more accurate due to how it creates 4 possibilities, then error-checks itself in order to grab
the value that is actually going to be used in the simulation.
*/

class MDB_Physics
{

public:
    bool quit;

    MDB_Physics(float time, float spring, float max_accel, float damping);
    ~MDB_Physics();

    void physicsLoop();

    void addObjects(std::vector<MDB_Shape*> objects);

    int detect_collisions(MDB_Shape* proposed_state, MDB_Vector2f our_vel, std::vector<MDB_Collision*> &collisions);

    void resolve_collisions(std::vector<MDB_Collision*> collisions);

    static int thread_wrapper(void* ptr);

private:
    int broadphase_actor_cull(MDB_Shape* us, std::vector<MDB_Shape*> their_actors, std::vector<MDB_Shape*> &collisions);
    int narrowphase_cull(
        MDB_Shape* ours, MDB_Vector2f our_vel, std::vector<MDB_Shape*> their_actors, std::vector<MDB_Collision*> &collisions
        );

    void addActor(MDB_Actor* newActor);

    MDB_Actor* getActor(void* ptr);

    std::vector<MDB_Actor*> actorList;

    //const TB_Vector2f ZERO_VECTOR;
    const float TIME_CONSTANT;
    const float SPRING_CONSTANT;
    const float MAX_VELOCITY;
    const float DAMPING_FACTOR;

};

#endif