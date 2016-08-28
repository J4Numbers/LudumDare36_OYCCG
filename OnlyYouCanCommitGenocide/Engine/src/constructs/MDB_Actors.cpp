#include "../../headers/constructs/MDB_Actors.hpp"

#include <algorithm>

MDB_Actor::MDB_Actor(MDB_Shape* initPos, MDB_TextureState* texture_dims) : MDB_Shape(initPos->get_origin(), MDB_E_STATIC),
texture_dims(texture_dims), MOVEMENT_CONSTANT(45.0f), DAMPING(0.99f), moveX(0.0f), moveY(0.0f),
lastTick(0), movementFlags(0x0000), directionalFlags(0x00)
{
    acceleration = new MDB_Vector2f(0, 0);
    velocity = new MDB_Vector2f(0, 0);
    displacement = new MDB_Vector2f(0, 0);
    lastDisp = new MDB_Vector2f(0, 0);
    prevDisp = new MDB_Vector2f(0, 0);
};


MDB_Actor::~MDB_Actor()
{
    delete acceleration;
    delete velocity;
    delete displacement;
    delete lastDisp;
    delete prevDisp;
}

MDB_Vector2f* MDB_Actor::getAcceleration()
{
    return acceleration;
}

void MDB_Actor::setAcceleration(MDB_Vector2f acc)
{
    *acceleration = acc;
}

MDB_Vector2f* MDB_Actor::getVelocity()
{
    return velocity;
}


void MDB_Actor::setVelocity(MDB_Vector2f vel)
{
    *velocity = vel;
}

MDB_Vector2f* MDB_Actor::getDisplacement()
{
    return displacement;
}

MDB_Vector2f* MDB_Actor::getLastDisplacement()
{
    return lastDisp;
}

MDB_Vector2f* MDB_Actor::getPreviousDisplacement()
{
    return prevDisp;
}

void MDB_Actor::setDisplacement(MDB_Vector2f disp)
{
    *displacement = disp;
}

SDL_Texture* MDB_Actor::getCurrentTexture(SDL_Rect* &r)
{
    return texture_dims->getCurrentBox(getCurrentState(), r);
}

void MDB_Actor::checkSwitchState()
{
    if ((movementFlags & 0x0002) == 0x0002)
    {
        switchState(MDB_E_FLY_RIGHT);
    }
    else
    {
        switchState(MDB_E_STATIC);
        resetFrameCounter();
    }
}

void MDB_Actor::move()
{
    //std::cout << secondsSinceUpdate << " seconds since last update..." << '\n';
    //std::cout << "Movement planned: " << (velocity.x * (movementConstant * secondsSinceUpdate)) << " pixels" << '\n';

    get_origin() = MDB_Maths::CalculateMovement(get_origin(), *displacement);

    if (((movementFlags & 0x06) == 0x00) && (velocity->x < 0.7f && velocity->x > -0.7f))
    {
        velocity->x = 0.0f;
        acceleration->x = 0.0f;
        displacement->x = 0.0f;
        movementFlags = movementFlags & 0xFF9F;
    }

    //position->x = position->x + velocity.x;
    //position->y = position->y + velocity.y;

    //nextMove.x = 0;
    //nextMove = nextMove & 0x08;
}

MDB_FakeShape* MDB_Actor::copy_shape() const
{
    MDB_FakeShape* fake = new MDB_FakeShape();

    if (shape_type == MDB_E_SHAPE_RECT)
    {
        fake->shape_type = MDB_E_SHAPE_RECT;
        fake->x = get_origin().x;
        fake->y = get_origin().y;

        MDB_RectShape* rct_shape = new MDB_RectShape;
        rct_shape->w = get_width();
        rct_shape->h = get_height();

        fake->shape = rct_shape;
    }
    else if (shape_type == MDB_E_SHAPE_CIRCLE)
    {
        fake->shape_type = MDB_E_SHAPE_CIRCLE;
        fake->x = get_origin().x;
        fake->y = get_origin().y;

        MDB_CircShape* circ_shape = new MDB_CircShape();
        circ_shape->radius = get_width() / 2;

        fake->shape = circ_shape;
    }
    else
    {
        fake->shape_type = MDB_E_SHAPE_UNKNOWN;
        fake->x = 0;
        fake->y = 0;
        fake->shape = nullptr;
    }

    return fake;
}


MDB_FakeShape* MDB_Actor::testMovement(MDB_Vector2f& proposedMove) const
{
    MDB_FakeShape* copy = copy_shape();
    MDB_Point2f p = MDB_Maths::CalculateMovement(get_origin(), proposedMove);
    copy->x += p.x;
    copy->y += p.y;
    return copy;
}

void MDB_Actor::submitMove(uint16_t move)
{
    movementFlags = move;
}

uint16_t MDB_Actor::getMoveFlags()
{
    return movementFlags;
}
