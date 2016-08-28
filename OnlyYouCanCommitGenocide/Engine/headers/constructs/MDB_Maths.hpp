#ifndef MDB_CALC_H
#define MDB_CALC_H

#include <cmath>

#include "../../include/SDL2/SDL.h"

#include "MDB_Enums.hpp"
#include "MDB_Structs.hpp"
#include "MDB_Common.hpp"

/**
* Static calculation class which holds a collection of methods which we use
* for general mathematics. These range from the simple calculation of movement
* (which honestly doesn't need to be here), to the more complex collision
* checking which goes on in here and covers more than I'd personally like...
*/
class MDB_Calc
{
public:
    static MDB_Point2f CalculateMovement(MDB_Point2f original, MDB_Vector2f movement);

    static bool HasCollided(MDB_Shape* a, MDB_Shape* b, MDB_Vector2f vel_a, MDB_Vector2f vel_b);
    static bool CircleCircleCollision(MDB_Point2f our_centre, float our_radius, MDB_Point2f their_centre, float their_radius);
    static bool RectRectCollision(MDB_Point2f our_centre, MDB_Rectangle* our_dims, MDB_Point2f their_centre, MDB_Rectangle* their_dims);
    static bool CircleRectCollision(MDB_Point2f cir_centre, float cir_radius, MDB_Point2f rect_centre, MDB_Rectangle* rect_dims);

    static bool InsideBox(MDB_Point2f test_point, MDB_Rectangle* rect, float ext);
    static bool InsideCircle(MDB_Point2f test_point, MDB_Circle* circ, float ext);

    static bool IntersectRectangleAndLine(MDB_Point2f rect_centre, MDB_Rectangle* rect_dims, MDB_Point2f* first_point, MDB_Point2f* second_point);

    static MDB_Vector2f GetWidthAndHeight(MDB_Shape* a);

    static SDL_Rect* CreateRectangle(MDB_Shape* shape, int screen_width, int screen_height, MDB_Vector2f camera_offset);
    static SDL_Rect* CreateTextRectangle(MDB_TextLocation* text, int screen_width, int screen_height, MDB_Vector2f camera_offset);
    static MDB_Vector2f GenerateBlockNormal(MDB_Point2f collision_point, MDB_Vector2f coll_dims, MDB_Point2f rect_centre, MDB_Rectangle* rect_dims, MDB_Point2f* point_on_plane);

    static MDB_Vector2f SymplecticEulerIntegration(MDB_Vector2f velocity, MDB_Vector2f acceleration, float time, MDB_Vector2f &newVelocity);
    static float SymplepticEulerImpact(float elasticity, MDB_Vector2f contact_normal, MDB_Vector2f joint_velocity, float mass_a, float mass_b);

    /**
    * Method which existed for working out Verlet displacements, but which was
    * later scrapped once collisions were introduced and I went 'nope'
    *
    * @param  acceleration     The acceleration of the object
    * @param  time             The timestep
    * @param  displacement     The displacement last time
    * @param  prevDisplacement The displacement before that
    * @return                  The new displacement
    */
    static MDB_Vector2f VerletIntegration(MDB_Vector2f acceleration, float time, MDB_Vector2f displacement,
        MDB_Vector2f prevDisplacement);
};

#endif