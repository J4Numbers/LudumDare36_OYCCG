#ifndef MDB_FINITESTATE_H
#define MDB_FINITESTATE_H

#include <cstdint>

//So, I guess that the state machine should be a collection of Rules,
// where rules are game logic items that determine what should be done...
//
//Meaning the 'enemy' subclass or, whatever I end up calling it, has a
// state machine embedded into it (I guess that a general actor can have
// one too actually). On a game loop, the actor will call a method in the
// state machine class to perform the current state (which will return a
// vector), after which, some checking will be done to see if the state
// has changed or will changed. If a change occurs, then we can update the
// texture or other aspects of the actor as they are needed.

class MDB_FiniteState
{

private:
    uint32_t current_state;
    uint32_t frame_counter;

protected:
    void switchState(uint32_t new_state);
    virtual void checkSwitchState() = 0;

    uint32_t getCurrentState() const;
    uint32_t getFrameCounter() const;
    void resetFrameCounter();
    void incrementFrameCounter();

public:
    MDB_FiniteState(uint32_t starting_state);
    virtual ~MDB_FiniteState();

};


#endif