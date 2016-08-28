#include "../../headers/constructs/MDB_File.hpp"

/**
 * Start work on differentiating different files (level files, etc.)
 * Possibly with a preamble header in a file of 4 8-bit numbers before
 * launching into the actual files.
 */
MDB_File::MDB_File(SDL_RWops* data) : dataObj(data), mode(0x03)
{
}

MDB_File::MDB_File(SDL_RWops* data, uint32_t m, uint32_t t) : dataObj(data), mode(m), filetype(t)
{
}

MDB_File::~MDB_File()
{
    if (SDL_RWclose(dataObj) != 0)
    {
        throw MDB_SDL_Exception();
    }
}

SDL_RWops* MDB_File::getRWops()
{
    return dataObj;
}

int MDB_File::getStreamSize()
{
    return SDL_RWsize(dataObj);
}

int MDB_File::getCurrentPosition()
{
    return SDL_RWseek(dataObj, 0, RW_SEEK_CUR);
}

int MDB_File::setCurrentPoisition(int startPoint)
{
    return SDL_RWseek(dataObj, startPoint, RW_SEEK_SET);
}

int MDB_File::gradualRead(int size, char* buff)
{
    if (mode & MDB_E_FILE_IO_R == MDB_E_FILE_IO_R)
    {
        return SDL_RWread(dataObj, buff, 1, size);
    }
    return -1;
}

int MDB_File::fullRead(char* buff)
{
    if (mode & MDB_E_FILE_IO_R == MDB_E_FILE_IO_R)
    {
        setCurrentPoisition(0);
        return SDL_RWread(dataObj, buff, getStreamSize(), 1);
    }
    return -1;
}

int MDB_File::writeData(int size, char* buffer)
{
    if (mode & MDB_E_FILE_IO_W == MDB_E_FILE_IO_W)
    {
        //Check if erronous and also move the pointer within the file to the new place
        return SDL_RWwrite(dataObj, buffer, 1, size);
    }
    return -1;
}

int MDB_File::writeData(MDB_File* copy)
{
    char buffer[32];
    int currWrit = 0;
    int theirSize = copy->getStreamSize();
    copy->setCurrentPoisition(0);

    while (currWrit < theirSize)
    {
        int read = copy->gradualRead(32, buffer);
        if (read != 0)
        {
            if (writeData(read, buffer) < read)
            {
                return -1;
            }
            currWrit += read;
        }
    }
    return 0;
}

int MDB_File::writeDataToFile(const char* filename)
{
    /*SDL_RWops* fileToWrite = SDL_RWFromFile(filename, "wb+");
    const char* preamble;
    int preambling[5] = {};

    switch (filetype)
    {
    case TB_FILE_IMAGE:
    preamble = { 15, 28, -105, 92, 9 };
    SDL_strlcpy(preamble, img, 5);
    break;

    case TB_FILE_LEVEL:
    char lvl[5] = { 82, 4, -55, -21, 86 };
    SDL_strlcpy(preamble, lvl, 5);
    break;

    case TB_FILE_AUDIO:
    char audio[5] = { 111, -32, 105, -2, 42 };
    SDL_strlcpy(preamble, audio, 5);
    break;

    default:
    char file[5] = { 0, 0, 0, 0, 0 };
    SDL_strlcpy(preamble, file, 5);
    break;
    }

    TB_Data wrapper(fileToWrite, filetype);
    wrapper.writeData(5, preamble);
    wrapper.writeData(this);

    //SDL_RWwrite(fileToWrite, amble, 5, 1);
    //SDL_RWseek(fileToWrite, 0, RW_SEEK_END);
    */
    return 0;
}