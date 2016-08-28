#ifndef MDB_ACTORS_H
#define MDB_ACTORS_H

//class TB_Physics;

#include "../../include/SDL2/SDL.h"

#include <iostream>

#include "MDB_Structs.hpp"
#include "MDB_Common.hpp"
#include "MDB_TextureState.hpp"

#include "MDB_Maths.hpp"

/**
* An actor in the system is any object which can move of its
* own free will (or of that of the player). So, actors are
* items such as the player, NPCs, enemy mobs, and maybe bullets,
* though those may go into their own projectile sub-class.
*/
class MDB_Actor : public MDB_Shape
{

public:
    /**
    * We know the starting state of any actor is resting in the right
    * direction, so we pass that in from the caller. We do, however,
    * need to pass in the shape of the actor along with the texture
    * system which defines how we display this actor to the player
    */
    MDB_Actor(MDB_Shape* initPos, MDB_TextureState* texture_dims);
    virtual ~MDB_Actor();

    /**
    * Implements the required functionality from TB_State which this
    * class is a sub-class of. Will perform specific checking to find
    * out what the current state of the actor is and react to stimuli
    * accordingly.
    */
    virtual void checkSwitchState();

    /**
    * Implements the required functionality of TB_Object and returns
    * the current texture that we're drawing from in order to display
    * something to the person playing the game.
    *
    * @param  r A variable within which we store the rectangle that
    *           is going to be shown within the SDL Texture, according
    *           to the current state of the program
    * @return   The Texture from which we're drawing the sub-rectangle:
    *               'r'.
    */
    virtual SDL_Texture* getCurrentTexture(SDL_Rect* &r);

    /**
    * @return The flags which describe the actor's current state of
    *             movement for this moment in time.
    */
    uint16_t getMoveFlags();

    /**
    * Override the current move with a new one (generally this parameter
    * is the old move flags bitwise OR'd or AND'd)
    *
    * @param move The move we're substituting for the one we were holding
    *             on to at the time
    */
    void submitMove(uint16_t move);

    /**
    * Implements required functionality of TB_Object and moves the Actor
    * according to the physics definitions that have been going on in the
    * background
    */
    virtual void move();

    /**
    * Override the acceleration with a new value (the change generally only
    * occurs within the x-axis due to how the acceleration on the y-axis is
    * a constant)
    *
    * @param acceleration The new acceleration we're using instead of that
    *                     old acceleration
    */
    void setAcceleration(MDB_Vector2f acceleration);

    /**
    * @return The current acceleration of the actor
    */
    MDB_Vector2f* getAcceleration();

    /**
    * Set our velocity with something new
    *
    * @param velocity The new velocity to set
    */
    void setVelocity(MDB_Vector2f velocity);

    /**
    * @return The current velocity of the actor
    */
    MDB_Vector2f* getVelocity();

    /**
    * Set where we're going to move the next time that the move() method is
    * called above
    *
    * @param move The move that we're going to perform, relative to our
    *             current position, wherever that may be
    */
    void setDisplacement(MDB_Vector2f move);

    /**
    * @return Our current relative displacement that is going to be
    *             used the next time move is called
    */
    MDB_Vector2f* getDisplacement();

    /**
    * @return The immediate previous displacement that we moved (so the
    *             distance we moved the last time move() was called)
    */
    MDB_Vector2f* getLastDisplacement();

    /**
    * @return The previous-displacement-but-one that we moved (so the
    *             distance we moved the time before the last that move() was
    *             called, whenever that was)
    */
    MDB_Vector2f* getPreviousDisplacement();

    /**
    * @return The mass of our object
    */
    float getMass();

    /**
    * Test a move on our object in order to see whether or not we would be
    * in a failing position if we did this move (so if we found a collision
    * or similar)
    *
    * This was originally used for an earlier iteration of the physics engine
    * and is now unused and deprecated. It should never be called.
    *
    * @param  proposedMove The move that we are proposing to this actor
    * @return              The shape of that resulting move that we could then
    *                          test in other areas of the code
    */
    MDB_Shape* testMovement(MDB_Vector2f& proposedMove) const;

    /**
    * @return The gravity of the situation.
    */
    float getPersonalGravity() const;

protected:
    /**
    * The texture dimensions of this actor
    */
    MDB_TextureAnimationFile* texture_dims;

    /**
    * The velocity of the actor
    */
    MDB_Vector2f* velocity;

    /**
    * The acceleration of the actor
    */
    MDB_Vector2f* acceleration;

    /**
    * The displacement of the actor
    */
    MDB_Vector2f* displacement;

    /**
    * The last displacement of the actor
    */
    MDB_Vector2f* lastDisp;

    /**
    * The displacement of the actor before the last displacement of the
    * actor
    */
    MDB_Vector2f* prevDisp;

    /**
     * Absolute maximum velocity that our actor can be moving at
     */
    const float MOVEMENT_CONSTANT;

    /**
     * Mass of the object
     */
    const float MASS;

    /**
     * Damping constant
     */
    const float DAMPING;

    /**
    * Movement controls that say when we actually move on a per-pixel
    * basis (we never move until we have a move on here above 1.0)
    */
    float moveX;

    /**
    * Identical to moveX
    */
    float moveY;

    /**
    * The personal gravity of this actor
    */
    float personalGravity;

    /**
    * Unused ticker previously used for frame counting
    */
    int lastTick;

    /**
    * Movement Flags are everything to do with our movement. They're a set of bitwise
    * flags set into 4 nibbles of whatever we need basically. The contents of the sets
    * of bits are as follows (from the right):
    *
    * First nibble (from the right)  : 0x000F
    *	The first nibble contains the distinct movement flags that say 'someone is
    *	telling us to go in this direction, so let's go in this direction'. They work
    *	in four directions: (left) 1010 (right)
    *		1 (first from the left)   : 0x0008 : Represents upwards motion
    *		0 (second from the left)  : 0x0004 : Represents leftwards motion
    *		1 (second from the right) : 0x0002 : Represents rightwards motion
    *		0 (first from the right)  : 0x0001 : Represents downwards motion
    *
    * Second nibble (from the right) : 0x00F0
    *	The second nibble is an extension of the first and deals in dirty-bits for
    *	moving. They're what allow us to definitively say that 'yes, we are slowing down
    *	now because they just released the key that said we were going this way'. Once
    *	we have slowed down to a stop in whichever of the four areas we have here, we
    *	wipe the bit: (left) 1010 (right)
    *		1 (first from the left)   : 0x0080 : Represents upwards change of direction
    *		0 (second from the left)  : 0x0040 : Represents leftwards change of direction
    *		1 (second from the right) : 0x0020 : Represents rightwards change of direction
    *		0 (first from the right)  : 0x0010 : Represents downwards change of direction
    *
    * Third nibble (from the right)  : 0x0F00
    *	The third nibble contains a few miscellaneous booleans that we need for any actor
    *	in the scene. It's the small variables that, while are important, don't have any
    *	need at all for a full 32-bit bool value: (left) 1010 (right)
    *		1
    *		0
    *		1 (second from the right) : 0x0200 : Represents jumping
    *		0 (first from the right)  : 0x0100 : Represents direction of the actor on the
    *			horizontal plane
    */
    uint16_t movementFlags;

    /**
     * Directional flags are the things that tell us which way we're pointing
     */
    uint8_t directionalFlags;

};

#endif