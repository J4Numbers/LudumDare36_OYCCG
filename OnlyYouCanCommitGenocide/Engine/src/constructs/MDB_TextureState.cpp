#include "../../headers/constructs/MDB_TextureState.hpp"

MDB_TextureState::MDB_TextureState(uint16_t width, uint16_t height, uint16_t texture_no, MDB_AnimationFile* textures)
    : last_texture(0), last_frame(0), bleed(0), actor_width(actor_width), actor_height(actor_height)
{
    for (int i = 0; i < texture_no; ++i)
    {
        state_map.insert(
            std::pair<uint16_t, MDB_AnimationFile>(
            textures[i].animation_type, textures[i]
            )
            );
    }
}

SDL_Texture* MDB_TextureState::getCurrentBox(uint16_t state, SDL_Rect* &ret)
{
    MDB_AnimationFile t = state_map.at(state);

    if (state == last_texture)
    {
        ++bleed;
        if (bleed > 23)
        {
            last_frame = (last_frame + 1) % t.frames;
        }
        bleed = bleed % 24;
    }
    else
    {
        bleed = 0;
        last_frame = 0;
    }

    last_texture = state;

    ret = new SDL_Rect();
    ret->x = t.frame_list[last_frame * 4];
    ret->y = t.frame_list[last_frame * 4 + 1];
    ret->w = static_cast<int16_t>(t.frame_list[last_frame * 4 + 2]);
    ret->h = static_cast<int16_t>(t.frame_list[last_frame * 4 + 3]);

    return t.connected_image->texture;
}
