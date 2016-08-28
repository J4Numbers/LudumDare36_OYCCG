#include "../../headers/constructs/MDB_System.hpp"

MDB_System::MDB_System() : bufferLength(0), bufferStart(0)
{
    eventBuffer = new SDL_Event[20];
}

MDB_System::~MDB_System()
{
    delete[] eventBuffer;
}

void MDB_System::addEvent(SDL_Event e)
{
    eventBuffer[(bufferStart + bufferLength) % 20] = e;
    if (bufferLength < 20)
    {
        bufferLength = bufferLength + 1;
    }
    else
    {
        bufferStart = (bufferStart + 1) % 20;
    }
}

void MDB_System::pollEvent()
{
    if (bufferLength > 0)
    {
        manageEvent(*(eventBuffer + bufferStart));

        bufferLength = bufferLength - 1;
        bufferStart = (bufferStart + 1) % 20;
    }
};
