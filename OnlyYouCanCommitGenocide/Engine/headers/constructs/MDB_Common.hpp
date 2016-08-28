#ifndef MDB_COMMON_H
#define MDB_COMMON_H

#include <string>
#include <vector>

#include "../../include/SDL2/SDL.h"

#include "MDB_Exceptions.hpp"
#include "MDB_File.hpp"

class MDB_Common
{
private:
    static MDB_File* get_file_for_writing(char* file_name, uint32_t file_type);
    static MDB_File* get_file_for_reading(char* file_name, uint32_t file_type);
    static MDB_File* get_file_for_readwrite(char* file_name, uint32_t file_type);
    static MDB_File* get_file_for_rw(char* file_name, char* mode, uint32_t mdb_file_mode, uint32_t file_type);
    static MDB_File* get_file(SDL_RWops* file, uint32_t mode, uint32_t file_type);

    static void pack_char_array(char* &byte_array, uint8_t bytes ... );
    static uint32_t unpack_char_array(char* &byte_array);

public:
    static void get_resource_path(char* & point, char* directory);

    static void generate_image_file(char* file_name, std::vector<void*> file_data);
    static void generate_animation_file(char* file_name, std::vector<void*> file_data);
    static void generate_actor_file(char* file_name, std::vector<void*> file_data);
    static void generate_config_file(char* file_name, std::vector<void*> file_data);

};

class MDB_Vector2f
{
public:
    float x, y;

    MDB_Vector2f();
    MDB_Vector2f(float x, float y);

    MDB_Vector2f operator+(const MDB_Vector2f& rhs) const;

    MDB_Vector2f operator+= (const MDB_Vector2f& rhs);

    MDB_Vector2f operator-(const MDB_Vector2f& rhs) const;

    MDB_Vector2f operator*(const float& rhs) const;

    MDB_Vector2f operator/(const float& rhs) const;

    float dot_product(const MDB_Vector2f& rhs) const;

    MDB_Vector2f operator=(const MDB_Vector2f& rhs);

    bool operator==(const MDB_Vector2f& rhs) const;

    bool operator!= (const MDB_Vector2f& rhs) const;

    MDB_Vector2f normalise() const;

    float get_magnitude() const;

};

class MDB_Point2f
{
public:
    float x, y;
    
    MDB_Point2f(float x, float y);
    MDB_Point2f();
    MDB_Point2f(const MDB_Point2f& rhs);
    MDB_Point2f(const MDB_Vector2f& rhs);
    
    MDB_Point2f operator+(const MDB_Point2f& rhs) const;
    MDB_Point2f operator+(const MDB_Vector2f& rhs) const;
    MDB_Point2f& operator+=(const MDB_Vector2f& rhs);

    MDB_Point2f operator-(const MDB_Point2f& rhs) const;
    MDB_Point2f operator-(const MDB_Vector2f& rhs) const;
    MDB_Point2f operator-=(const MDB_Vector2f& rhs);

    MDB_Point2f operator*(const float& rhs) const;
    MDB_Point2f operator*(const MDB_Vector2f& rhs) const;

    MDB_Point2f operator/(const float& rhs) const;
    MDB_Point2f operator/(const MDB_Vector2f& rhs) const;

    MDB_Point2f operator=(const MDB_Point2f& rhs);

    bool operator==(const MDB_Point2f& rhs) const;
    bool operator!=(const MDB_Point2f& rhs) const;

    float dist_between(MDB_Point2f& rhs) const;

    MDB_Vector2f vector_between(MDB_Point2f& rhs) const;
};

const MDB_Vector2f ZERO_VECTOR(0.0f, 0.0f);
const MDB_Point2f ZERO_POINT(0.0f, 0.0f);

#endif