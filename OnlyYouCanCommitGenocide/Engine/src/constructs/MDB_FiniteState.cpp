#include "../../headers/constructs/MDB_FiniteState.hpp"

MDB_FiniteState::MDB_FiniteState(uint32_t starting_state) : current_state(starting_state)
{
}

MDB_FiniteState::~MDB_FiniteState()
{
}

void MDB_FiniteState::switchState(uint32_t new_state)
{
    current_state = new_state;
}

uint32_t MDB_FiniteState::getCurrentState() const
{
    return current_state;
}

uint32_t MDB_FiniteState::getFrameCounter() const
{
    return frame_counter;
}

void MDB_FiniteState::resetFrameCounter()
{
    frame_counter = 0;
}

void MDB_FiniteState::incrementFrameCounter()
{
    ++frame_counter;
}
