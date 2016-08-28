#ifndef MDB_COMMON_H
#define MDB_COMMON_H

#include <string>
#include <vector>

#include "../../include/SDL2/SDL.h"

#include "MDB_Exceptions.hpp"
#include "MDB_File.hpp"
#include "MDB_FiniteState.hpp"

class MDB;
class MDB_Screen;

class MDB_Common
{
private:
    static MDB* central_mdb;
    static MDB_Screen* central_mdb_screen;

    static MDB_File* get_file_for_writing(char* file_name, uint32_t file_type);
    static MDB_File* get_file_for_reading(char* file_name, uint32_t file_type);
    static MDB_File* get_file_for_readwrite(char* file_name, uint32_t file_type);
    static MDB_File* get_file_for_rw(char* file_name, char* mode, uint32_t mdb_file_mode, uint32_t file_type);
    static MDB_File* get_file(SDL_RWops* file, uint32_t mode, uint32_t file_type);

    static void pack_char_array(char* &byte_array, uint8_t bytes ... );
    //static uint32_t unpack_char_array(char* &byte_array);

public:
    static void get_resource_path(char* & point, char* directory);

    static void load_mdb(MDB* _central_mdb);
    static void load_mdb_screen(MDB_Screen* _mdb_screen);

    static MDB* request_mdb();
    static MDB_Screen* request_mdb_screen();

    //static void generate_image_file(char* file_name, std::vector<void*> file_data);
    //static void generate_animation_file(char* file_name, std::vector<void*> file_data);
    //static void generate_actor_file(char* file_name, std::vector<void*> file_data);
    //static void generate_config_file(char* file_name, std::vector<void*> file_data);

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

class MDB_Shape : protected MDB_FiniteState
{
protected:
    uint32_t shape_type;
    MDB_Point2f* centre;

public:
    MDB_Shape(MDB_Point2f origin, uint32_t obj_shape, uint32_t starting_state);
    virtual ~MDB_Shape();

    virtual void move() = 0;

    virtual void checkSwitchState() = 0;

    uint32_t get_shape_type() const;
    
    MDB_Point2f get_origin() const;
    virtual uint32_t get_width() const = 0;
    virtual uint32_t get_height() const = 0;
    virtual SDL_Rect generate_rectangle() const = 0;

    void set_origin(MDB_Point2f _origin);
};

class MDB_Rectangle : protected MDB_Shape
{
protected:
    uint32_t w, h;

public:
    MDB_Rectangle(int _x, int _y, int _w, int _h);
    MDB_Rectangle(MDB_Point2f _origin, int _w, int _h);
    MDB_Rectangle(SDL_Rect & rhs);
    virtual ~MDB_Rectangle();

    virtual uint32_t get_width() const;
    virtual uint32_t get_height() const;

    virtual SDL_Rect generate_rectangle() const;
};

class MDB_Circle : protected MDB_Shape
{
protected:
    uint32_t radius;

public:
    MDB_Circle(int _x, int _y, int _radius);
    MDB_Circle(MDB_Point2f _origin, int _radius);
    virtual ~MDB_Circle();

    virtual uint32_t get_width() const;
    virtual uint32_t get_height() const;

    virtual SDL_Rect generate_rectangle() const;
};

const MDB_Vector2f ZERO_VECTOR(0.0f, 0.0f);
const MDB_Point2f ZERO_POINT(0.0f, 0.0f);

const SDL_Rect ZERO_RECT = { 0, 0, 0, 0 };

#endif