#ifndef MDB_TEXTURESTATE_H
#define MDB_TEXTURESTATE_H

#include <map>

#include "../../include/SDL2/SDL.h"

#include "MDB_Structs.hpp"

/**
* The texture class is also a sort of state-box. We have a map of all the
* possible texture areas that we could have for this actor, then input the
* current state and get the current texture and frame which is to be used to
* display the actor.
*
* I may or may not be slightly chuffed with it...
*/
class MDB_TextureState
{
private:
    std::map<uint16_t, MDB_AnimationFile> state_map;

    uint16_t last_texture;
    uint8_t last_frame;
    uint8_t bleed;

    uint16_t actor_width;
    uint16_t actor_height;

public:
    MDB_TextureState(uint16_t actor_width, uint16_t actor_height, uint16_t texture_no, MDB_AnimationFile* textures);

    SDL_Texture* getCurrentBox(uint16_t state, SDL_Rect* &ret);
};

#endif