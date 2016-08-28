#include "../headers/MDB_Physics.hpp"

MDB_Physics::MDB_Physics(float time, float spring, float max_vel, float damping)
    : quit(false), TIME_CONSTANT(time), SPRING_CONSTANT(spring),
    MAX_VELOCITY(max_vel), DAMPING_FACTOR(damping)
{
}

MDB_Physics::~MDB_Physics()
{
}

void MDB_Physics::physicsLoop()
{
    for (auto &actor : actorList)
    {
        uint16_t move = actor->getMoveFlags();

        //Let's try doing an always-update loop instead of checking to see whether the
        // player is on the floor before we do this
        MDB_Vector2f acceleration = *actor->getAcceleration();

        //Slight reminder for myself, 0x60 & move == 0x60 is necessary because if only
        // one button is held down, 0x60 & move will still return true because of a non-
        // -zero return value. The only way to force this is to say that we will only
        // accept a true and complete AND statement of == 0x60
        if (((move & 0x0060) == 0x0060) || ((move & 0x0060) == 0x0000) ||
            ((move & 0x0040) == 0x0040) || ((move & 0x0020) == 0x0020))
        {
            if (actor->getVelocity()->x != 0)
            {
                acceleration.x = (std::abs(actor->getVelocity()->x) / actor->getVelocity()->x) * -8;
            }
        }
        //Other slight reminder, 0x0060 == 0x0000 is to check for complete inaction on
        // the x plane. Also, this whole thing is just decelleration really... That would
        // have been simpler to state I guess...

        if (((move & 0x0008) == 0x0008) && ((move & 0x0200) != 0x0200))
        {
            MDB_Vector2f velocity = *actor->getVelocity();
            velocity.y = -15;
            actor->setVelocity(velocity);
            actor->submitMove(move | 0x0200);
        }
        if (move & 0x0080)
        {
        }
        if ((move & 0x0006) == 0x0006)
        {
            acceleration.x = -(acceleration.x);
        }
        else
            if ((move & 0x0004) == 0x0004)
            {
                acceleration.x = -1.0f;
            }
            else
                if ((move & 0x0002) == 0x0002)
                {
                    acceleration.x = 1.0f;
                }

        if ((actor->getVelocity()->x > MAX_VELOCITY &&
            acceleration.x > 0) || (acceleration.x < 0 &&
            actor->getVelocity()->x < -MAX_VELOCITY))
        {
            acceleration.x = 0;
        }

        actor->setAcceleration(acceleration);


        //Stopping problem - bounces when we hit the floor due to how Verlet tracks displacements
        // and, therefore, reverses velocity when we stop.
        MDB_Vector2f* proposed = new MDB_Vector2f();
        std::vector<MDB_Collision*> detected_collisions;
        int no_of_colls = 0;

        no_of_colls = detect_collisions(actor, *actor->getVelocity(), detected_collisions);

        if (no_of_colls > 0)
        {
            resolve_collisions(detected_collisions);
        }

        *proposed = MDB_Maths::SymplecticEulerIntegration(
            *actor->getVelocity(), *actor->getAcceleration(),
            TIME_CONSTANT, *actor->getVelocity()
            );

        actor->setDisplacement(*proposed);
        // std::cout << "Current actor position is: x: " << actor->getShape()->pos->x << ", y: " << actor->getShape()->pos->y << '\n';
        // std::cout << "Proposed displacement for actor was: x: " << proposed->x << ", y: " << proposed->y << '\n';
        delete proposed;
    }

    for (auto &a : actorList)
    {
        a->move();
    }
}

int MDB_Physics::detect_collisions(MDB_Actor* proposed_state, MDB_Vector2f our_vel, std::vector<MDB_Collision*> &collisions)
{
    std::vector<MDB_Actor*> actorColls;
    int colls = broadphase_actor_cull(proposed_state, actorList, actorColls);
    if (colls > 0)
    {
        colls = narrowphase_cull(proposed_state, our_vel, actorColls, collisions);
    }
    return colls;
}

void MDB_Physics::resolve_collisions(std::vector<MDB_Collision*> collisions)
{
    for (auto &c : collisions)
    {
        //Move the object out of the other party before we do anything else
        MDB_Actor* us = getActor(c->object_a);
        MDB_Actor* them = getActor(c->object_b);

        us->setDisplacement(MDB_Vector2f(c->contact_normal_x, c->contact_point_y) * -c->contact_depth);
        us->move();

        delete c;
    }
}


int MDB_Physics::broadphase_actor_cull(MDB_Actor* us, std::vector<MDB_Actor*> their_actors, std::vector<MDB_Actor*> &collisions)
{
    std::vector<MDB_Actor*> possibly_colliding;
    int count = 0;

    for (auto &actor : their_actors)
    {
        if (us != actor)
        {
            //Broadphase culling here
            possibly_colliding.push_back(actor);
            ++count;
        }
    }

    collisions = possibly_colliding;
    return count;
}

int MDB_Physics::narrowphase_cull(
    MDB_Actor* ours, MDB_Vector2f our_vel, std::vector<MDB_Actor*> their_actors, std::vector<MDB_Collision*> &collisions)
{
    std::vector<MDB_Collision*> colliding;
    int count = 0;

    MDB_Collision* coll;

    for (auto &them : their_actors)
    {
        if (ours != them)
        {
            coll = new MDB_Collision();

            if (MDB_Maths::HasCollided(ours, them, our_vel, *them->getVelocity(), coll))
            {
                colliding.push_back(coll);
                ++count;
            }
            else
            {
                delete coll;
            }
        }
    }

    collisions = colliding;
    return count;
}

void MDB_Physics::addObjects(std::vector<MDB_Actor*> objects)
{
    for (auto &o : objects)
    {
        addActor(o);
    }
}


void MDB_Physics::addActor(MDB_Actor* newActor)
{
    actorList.push_back(newActor);
}

MDB_Actor* MDB_Physics::getActor(void* ptr)
{
    for (auto &a : actorList)
    {
        if (a == ptr)
        {
            return a;
        }
    }
    return nullptr;
}

int MDB_Physics::thread_wrapper(void* ptr)
{
    MDB_Physics* self = static_cast<MDB_Physics*>(ptr);
    while (!self->quit)
    {
        self->physicsLoop();
        SDL_Delay(1000 / 600);
    }
    return 0;
}
