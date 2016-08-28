#ifndef MDB_STRUCTS_H
#define MDB_STRUCTS_H

#include "../../include/SDL2/SDL.h"

#include "MDB_File.hpp"

struct MDB_Room
{
    uint32_t width;
    uint32_t height;

//Flags include such things as scroll direction and the speed of scroll
    uint32_t flags;
};

struct MDB_SDLKeyBindings
{
    uint32_t mdb_bind;
    int32_t sdl_bind;
};

struct MDB_KeyBindings
{
    uint32_t mdb_bind;
    uint32_t key_state;
    uint32_t action;
};

struct MDB_Image
{
    uint32_t img_size;
    uint32_t width;
    uint32_t height;
    char* img_slug;
    MDB_File* img_file;
    SDL_Texture* texture;
};

struct MDB_AnimationFile
{
    uint32_t frames;
//See enums in the 0x73XX range
    uint32_t animation_type;
    char* img_slug;
    uint32_t* frame_list;
    MDB_Image* connected_image;
};

struct MDB_TextureAnimationFile
{
    char* animation_slug;
    uint32_t no_textures;
    MDB_AnimationFile* animations;
};

struct MDB_Attack
{
    uint32_t damage;
    uint32_t speed;
    char* animation_slug;

    MDB_TextureAnimationFile* animations;
};

struct MDB_AttackChance
{
    MDB_Attack attack;
    float chance;
};

struct MDB_ActorVariations
{
    uint32_t health;
//See MDB_E_ 0x72XX spaces
    uint32_t type;

    MDB_AttackChance* attacks;
};

struct MDB_DropChance
{
    float drop_chance;
    char* drop;
};

struct MDB_TextLocation
{
    int32_t x, y;
    uint32_t w, h;
    SDL_Texture* t;
};

struct MDB_RectShape
{
    int32_t x, y;
    uint32_t w, h;
};

struct MDB_CircShape
{
    int32_t x, y;
    uint32_t radius;
};

struct MDB_FakeShape
{
    int32_t x, y;
    void* shape;
    uint32_t shape_type;
};

struct MDB_Collision
{
    void* object_a;
    void* object_b;

    float joint_vel_x, joint_vel_y;

    float contact_point_x, contact_point_y;
    float contact_normal_x, contact_normal_y;
    float contact_depth;
};

#endif