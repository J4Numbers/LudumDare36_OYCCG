#ifndef MDB_COMMON_H
#define MDB_COMMON_H

#include <string>

#include "../../include/SDL2/SDL.h"

#include "MDB_Exceptions.hpp"

class MDB_Common
{

public:
    static void get_resource_path(char* & point, char* directory);

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