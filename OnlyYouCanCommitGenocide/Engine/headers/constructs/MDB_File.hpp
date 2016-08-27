#ifndef MDB_FILE_H
#define MDB_FILE_H

#include "../../include/SDL2/SDL.h"

#include "MDB_Enums.hpp"
#include "MDB_Exceptions.hpp"

/**
 * Our own abstraction for FileIO in that this means we have an OO-approach to
 * it and we only have two real options: read and write.
 */
class MDB_File
{
    
public:
    /**
     * Construct our object from a data object and assume default mode of rw
     */
    MDB_File(SDL_RWops* dataObj);

    /**
     * Construct our object from a data object and specify our mode
     */
    MDB_File(SDL_RWops* dataObj, uint8_t mode);
    ~MDB_File();

    /**
     * @return The data object below us
     */
    SDL_RWops* getRWops();

    /**
     * @return The size of the data object stream
     */
    int getStreamSize();

    /**
     * @return The current position within the stream
     */
    int getCurrentPosition();

    /**
     * Set the current position in the stream relative to the start of the
     * stream
     *
     * @param  startPoint The number of bytes in our new start point will be
     * @return            0 on success, something else otherwise
     */
    int setCurrentPoisition(int startPoint);

    /**
     * Read in a number of characters from a buffer
     *
     * @param  size The size that we want to read in to the buffer
     * @param  buff The buffer that we're copying our reads into
     * @return      The number of characters read
     */
    int gradualRead(int size, char* buff);

    /**
     * Read the whole file and dump it into the buffer
     *
     * @param  buff The buffer that's going to get dumped in
     * @return      The size of the buffer
     */
    int fullRead(char* buff);

    /**
     * We write some data to the IO from a buffer
     *
     * @param  size   The amount of data we want to write to the IO
     * @param  buffer The buffer we're reading from to write to the IO
     * @return        The amount of data written to the buffer
     */
    int writeData(int size, char* buffer);

    /**
     * Effective copy constructor for TB_Data classes as we copy across the
     * data in one io object to the other in the copy place
     *
     * @param  copy What we're copying to
     * @return      0 on success, -1 otherwise
     */
    int writeData(MDB_File* copy);

    /**
     * Dead method. Doesn't do anything.
     *
     * @param  filename The name of the file
     * @return          0
     */
    int writeDataToFile(const char* filename);

private:
    /**
     * The data object beneath us that we hide
     */
    SDL_RWops* dataObj;

    /**
     * The IO mode for the file (read/write locked)
     */
    uint8_t mode;

    /**
     * The type of file we're looking at (unused)
     * See 0x74XX space in enums for this
     */
    uint32_t filetype;

    /**
     * Current position within the file
     */
    int position;

};

#endif