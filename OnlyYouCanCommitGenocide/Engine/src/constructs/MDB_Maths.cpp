#include "../../headers/constructs/MDB_Maths.hpp"

MDB_Point2f MDB_Maths::CalculateMovement(MDB_Point2f original, MDB_Vector2f movement)
{
    return original + movement;
}

MDB_Vector2f MDB_Maths::GenerateBlockNormal(MDB_Point2f collision_point, MDB_Vector2f coll_dims, MDB_Point2f rect_centre, SDL_Rect rect_dims, MDB_Point2f* point_on_plane)
{
    MDB_Vector2f resolution;

    //We have several cases to examine... Let's first look at the point where the collision
    // has been isolated to the top left quadrant of our rectangle
    if (collision_point.x < rect_centre.x && collision_point.y < rect_centre.y)
    {
        //And have a simple response algorithm which states: the point which is further from the outside
        // is the one that we take priority for. Let's look at whether the vertical axis has priority
        // first (because depth on x being smaller means it's closer to the edge vertically)
        if (std::abs((rect_centre.x - rect_dims.w / 2) - (collision_point.x + coll_dims.x)) <
            std::abs((rect_centre.y - rect_dims.h / 2) - (collision_point.y + coll_dims.y)))
        {
            // <-| is the plane orientation for this scenario
            resolution.x = -1.0f;
            resolution.y = 0.0f;
        }
        else
        {
            // ^
            // | Is the plane orientation for this scenario
            //---
            resolution.x = 0.0f;
            resolution.y = -1.0f;
        }
    }
    //Second case is for the bottom left quadrant of the rectangle
    else if (collision_point.x < rect_centre.x && collision_point.y > rect_centre.y)
    {
        if (std::abs((rect_centre.x - rect_dims.w / 2) - (collision_point.x + coll_dims.x)) <
            std::abs((rect_centre.y + rect_dims.h / 2) - (collision_point.y - coll_dims.y)))
        {
            // <-| is the plane orientation for this scenario
            resolution.x = -1.0f;
            resolution.y = 0.0f;
        }
        else
        {
            //___
            // | is the plane orientation for this scenario
            // V
            resolution.x = 0.0f;
            resolution.y = 1.0f;
        }
    }
    //Third case is for the top right quadrant of the rectangle
    else if (collision_point.x > rect_centre.x && collision_point.y < rect_centre.y)
    {
        if (std::abs((rect_centre.x + rect_dims.w / 2) - (collision_point.x - coll_dims.x)) <
            std::abs((rect_centre.y - rect_dims.h / 2) - (collision_point.y + coll_dims.y)))
        {
            // |-> is the plane orientation for this scenario
            resolution.x = 1.0f;
            resolution.y = 0.0f;
        }
        else
        {
            // ^
            // | is the plane orientation for this scenario
            //---
            resolution.x = 0.0f;
            resolution.y = -1.0f;
        }
    }
    //Final case is for the bottom right quadrant of the rectangle
    else
    {
        if (std::abs((rect_centre.x + rect_dims.w / 2) - (collision_point.x - coll_dims.x)) <
            std::abs((rect_centre.y + rect_dims.h / 2) - (collision_point.y - coll_dims.y)))
        {
            // |-> is the plane orientation for this scenario
            resolution.x = 1.0f;
            resolution.y = 0.0f;
        }
        else
        {
            //___
            // | is the plane orientation for this scenario
            // V
            resolution.x = 0.0f;
            resolution.y = 1.0f;
        }
    }

    if (point_on_plane != nullptr)
    {
        point_on_plane->x = rect_centre.x + (resolution.x * (rect_dims.w / 2));
        point_on_plane->y = rect_centre.y + (resolution.y * (rect_dims.h / 2));
    }

    return resolution;
}


SDL_Rect* MDB_Maths::CreateRectangle(MDB_Shape* shape, int screen_width, int screen_height, MDB_Vector2f camera_offset)
{
    SDL_Rect* t = new SDL_Rect();

    switch (shape->get_shape_type())
    {
    case MDB_E_SHAPE_RECT:
    case MDB_E_SHAPE_CIRCLE:
        t->x = shape->get_origin().x + (screen_width / 2) + camera_offset.x;
        t->y = shape->get_origin().y + (screen_height / 2) + camera_offset.y;
        t->w = shape->get_width();
        t->h = shape->get_height();
        break;
    default:
        break;
    }

    return t;
}

SDL_Rect* MDB_Maths::CreateTextRectangle(MDB_TextLocation* text, int screen_width, int screen_height, MDB_Vector2f camera_offset)
{
    SDL_Rect* t = new SDL_Rect();

    t->x = text->x + (screen_width / 2) + camera_offset.x;
    t->y = text->y + (screen_height / 2) + camera_offset.y;
    t->w = text->w;
    t->h = text->h;

    return t;
}


bool MDB_Maths::HasCollided(MDB_Shape* a, MDB_Shape* b, MDB_Vector2f vel_a, MDB_Vector2f vel_b, MDB_Collision*& res)
{
    uint32_t collided = MDB_E_COLL_NONE;

    switch (a->get_shape_type())
    {
    case MDB_E_SHAPE_RECT:
        switch (b->get_shape_type())
        {
        case MDB_E_SHAPE_RECT:
            collided = MDB_Maths::RectRectCollision(b->get_origin(), b->generate_rectangle(), a->get_origin(), a->generate_rectangle())
                ? MDB_E_COLL_RECT_RECT : MDB_E_COLL_NONE;
            break;
        case MDB_E_SHAPE_CIRCLE:
            collided = MDB_Maths::CircleRectCollision(b->get_origin(), b->get_height(), a->get_origin(), a->generate_rectangle())
                ? MDB_E_COLL_RECT_CIRLE : MDB_E_COLL_NONE;
            break;
        default:
            break;
        }
        break;
    case MDB_E_SHAPE_CIRCLE:
        switch (b->get_shape_type())
        {
        case MDB_E_SHAPE_RECT:
            collided = MDB_Maths::CircleRectCollision(a->get_origin(), a->get_height(), b->get_origin(), b->generate_rectangle())
                ? MDB_E_COLL_RECT_CIRLE : MDB_E_COLL_NONE;
            break;
        case MDB_E_SHAPE_CIRCLE:
            collided = MDB_Maths::CircleCircleCollision(a->get_origin(), a->get_height(), b->get_origin(), b->get_height())
                ? MDB_E_COLL_CIRCLE_CIRCLE : MDB_E_COLL_NONE;
            break;
        default:
            break;
        }
        break;
    default:
        break;
    }

    if (collided != MDB_E_COLL_NONE && res != nullptr)
    {
        float dist = a->get_origin().dist_between(b->get_origin());

        res->object_a = a;
        res->object_b = b;

        MDB_Point2f diff = a->get_origin() - b->get_origin();
        MDB_Vector2f joint_vel = vel_b - vel_a;
        res->joint_vel_x = joint_vel.x;
        res->joint_vel_y = joint_vel.y;

        MDB_Point2f* our_pos = new MDB_Point2f(a->get_origin());
        MDB_Point2f* their_pos = new MDB_Point2f(b->get_origin());

        MDB_Vector2f orientation, contact_normal;
        MDB_Point2f contact_point;
        float ffdist;
        float rect_radius;

        if (collided & (MDB_E_COLL_RECT_RECT | MDB_E_COLL_RECT_CIRLE))
        {
            orientation = MDB_Maths::GenerateBlockNormal(a->get_origin(), MDB_Vector2f(a->get_width() / 2, a->get_height() / 2), b->get_origin(), b->generate_rectangle(), their_pos);
            contact_normal = orientation * -1;
            res->contact_normal_x = contact_normal.x;
            res->contact_normal_y = contact_normal.y;
            ffdist = std::abs(std::abs(orientation.dot_product(MDB_Vector2f(a->get_origin().x, a->get_origin().y))) - MDB_Vector2f(their_pos->x, their_pos->y).get_magnitude());
        }

        switch (collided)
        {
        case MDB_E_COLL_CIRCLE_CIRCLE:
            contact_point = a->get_origin() - static_cast<MDB_Point2f>(contact_normal * (a->get_height() - res->contact_depth));
            res->contact_depth = (a->get_height() + b->get_height()) - dist;
            break;
        case MDB_E_COLL_RECT_RECT:
            rect_radius = (orientation.x == 0) ? a->get_height() / 2 : a->get_width() / 2;
            res->contact_depth = rect_radius - ffdist;
            contact_point = a->get_origin() - (orientation * (rect_radius - res->contact_depth));
            break;
        case MDB_E_COLL_RECT_CIRLE:
            if (a->get_shape_type() == MDB_E_SHAPE_CIRCLE)
            {
                res->contact_depth = a->get_height() - ffdist;
                contact_point = a->get_origin() - (orientation * (a->get_height() - res->contact_depth));
            }
            else
            {
                res->contact_depth = b->get_height();
                contact_point = b->get_origin() - (orientation * (b->get_height() - res->contact_depth));
            }
            break;
        default:
            contact_point = MDB_Point2f();
            res->contact_depth = 0.0f;
            break;
        }

        res->contact_point_x = contact_point.x;
        res->contact_point_y = contact_point.y;

        delete our_pos;
        delete their_pos;
    }

    return (collided != MDB_E_COLL_NONE);
}

bool MDB_Maths::CircleCircleCollision(MDB_Point2f our_centre, float our_radius, MDB_Point2f their_centre, float their_radius)
{
    return our_centre.dist_between(their_centre) < (our_radius + their_radius);
}

bool MDB_Maths::RectRectCollision(MDB_Point2f our_centre, SDL_Rect our_dims, MDB_Point2f their_centre, SDL_Rect their_dims)
{
    MDB_Point2f theirBL = MDB_Point2f(
        their_centre.x - (their_dims.w / 2),
        their_centre.y - (their_dims.h / 2)
        );

    MDB_Point2f theirBR = MDB_Point2f(
        their_centre.x + (their_dims.w / 2),
        their_centre.y - (their_dims.h / 2)
        );

    MDB_Point2f theirTL = MDB_Point2f(
        their_centre.x - (their_dims.w / 2),
        their_centre.y + (their_dims.h / 2)
        );

    MDB_Point2f theirTR = MDB_Point2f(
        their_centre.x + (their_dims.w / 2),
        their_centre.y + (their_dims.h / 2)
        );

    MDB_Point2f ourBL = MDB_Point2f(
        our_centre.x - (our_dims.w / 2),
        our_centre.y - (our_dims.h / 2)
        );

    MDB_Point2f ourBR = MDB_Point2f(
        our_centre.x + (our_dims.w / 2),
        our_centre.y - (our_dims.h / 2)
        );

    MDB_Point2f ourTL = MDB_Point2f(
        our_centre.x - (our_dims.w / 2),
        our_centre.y + (our_dims.h / 2)
        );

    MDB_Point2f ourTR = MDB_Point2f(
        our_centre.x + (our_dims.w / 2),
        our_centre.y + (our_dims.h / 2)
        );

    return (MDB_Maths::InsideBox(theirBL, our_dims, 0) || MDB_Maths::InsideBox(theirBR, our_dims, 0) ||
        MDB_Maths::InsideBox(theirTL, our_dims, 0) || MDB_Maths::InsideBox(theirTR, our_dims, 0)) ||
        (MDB_Maths::InsideBox(ourBL, their_dims, 0) || MDB_Maths::InsideBox(ourBR, their_dims, 0) ||
        MDB_Maths::InsideBox(ourTL, their_dims, 0) || MDB_Maths::InsideBox(ourTR, their_dims, 0));
}

bool MDB_Maths::CircleRectCollision(MDB_Point2f cir_centre, float cir_radius, MDB_Point2f rect_centre, SDL_Rect rect_dims)
{
    MDB_Point2f ourBL = MDB_Point2f(
        rect_centre.x - (rect_dims.w / 2),
        rect_centre.y - (rect_dims.h / 2)
        );

    MDB_Point2f ourBR = MDB_Point2f(
        rect_centre.x + (rect_dims.w / 2),
        rect_centre.y - (rect_dims.h / 2)
        );

    MDB_Point2f ourTL = MDB_Point2f(
        rect_centre.x - (rect_dims.w / 2),
        rect_centre.y + (rect_dims.h / 2)
        );

    MDB_Point2f ourTR = MDB_Point2f(
        rect_centre.x + (rect_dims.w / 2),
        rect_centre.y + (rect_dims.h / 2)
        );

    //Checking a Square-Circle overlap is a bit more complex,
    // requiring that we check two cases in particular. That
    // is to say, the case where the point is within the
    // range of one of our four sides, and the case where the
    // point is within range of our corners

    //Let's first look at the corners as they are the 
    // easiest to check, starting with the top left
    if (MDB_Maths::InsideCircle(ourTL, cir_centre, cir_radius, 0)
        //Top right
        || MDB_Maths::InsideCircle(ourTR, cir_centre, cir_radius, 0)
        //Bottom left
        || MDB_Maths::InsideCircle(ourBL, cir_centre, cir_radius, 0)
        //Bottom right
        || MDB_Maths::InsideCircle(ourBR, cir_centre, cir_radius, 0))
    {
        //We only need one of those to be true before we can
        // shout that we've found the answer to the caller
        return true;
    }

    //But, if we didn't, we still need to check that the
    // circle is not within range of one of our sides,
    // without triggering the corner radius
    return MDB_Maths::InsideBox(cir_centre, rect_dims, cir_radius);
}

bool MDB_Maths::InsideCircle(MDB_Point2f test_point, MDB_Point2f centre_point, float radius, float ext)
{
    return centre_point.dist_between(test_point) < (radius + ext);
}


bool MDB_Maths::InsideBox(MDB_Point2f test_point, SDL_Rect rect, float ext)
{
    //Let's construct a list of sides that we can get information
    // from. These are our actual sides of this shape, with the
    // extension added on if applicable
    float thisL = rect.x - ext;
    float thisR = rect.x + rect.w + ext;
    float thisT = rect.y + rect.h + ext;
    float thisB = rect.y - ext;

    //    std::cout << "Comparing point " << other << " and seeing if it is "
    //        << "within the box: L:" << thisL << ", R:" << thisR << ", T:"
    //        << thisR << ", B: " << thisB << '\n';

    //Now let's look at whether the point falls within our box
    // with a large AND statement asking whether the point falls
    // within all four sides of our shape
    if (test_point.x <= thisR && test_point.x >= thisL
        && test_point.y <= thisT && test_point.y >= thisB)
    {
        //Now we have edge cases. It's undesirable in these
        // circumstances to have points which lie in the
        // space inverted behind each corner of our square,
        // so we now treat this square like two rectangles
        // instead and ask whether our point lies within
        // either of them before we finalise our result
        if (test_point.x <= thisR && test_point.x >= thisL
            && test_point.y <= rect.y + rect.h
            && test_point.y >= rect.y)
        {
            return true;
        }
        if (test_point.y <= thisT && test_point.y >= thisB
            && test_point.x <= rect.x + rect.w
            && test_point.x >= rect.x)
        {
            return true;
        }
    }

    return false;
}

bool MDB_Maths::IntersectRectangleAndLine(MDB_Point2f rect_centre, SDL_Rect rect_dims, MDB_Point2f* first_point, MDB_Point2f* second_point)
{
    float u = second_point->y - first_point->y;
    float v = first_point->x - second_point->x;
    float w = (first_point->x * second_point->y) - (second_point->x * first_point->y);

    float rectTL = u * (rect_centre.x - rect_dims.w / 2) + v * (rect_centre.y + rect_dims.h / 2) + w;
    float rectTR = u * (rect_centre.x + rect_dims.w / 2) + v * (rect_centre.y + rect_dims.h / 2) + w;
    float rectBL = u * (rect_centre.x - rect_dims.w / 2) + v * (rect_centre.y - rect_dims.h / 2) + w;
    float rectBR = u * (rect_centre.x + rect_dims.w / 2) + v * (rect_centre.y - rect_dims.h / 2) + w;

    if ((rectTL > 0 && rectTR > 0 && rectBL > 0 && rectBR > 0) ||
        (rectTL < 0 && rectTR < 0 && rectBL < 0 && rectBR < 0))
    {
        bool found = false;
        bool was_in = false;
        bool in;

        float dist = first_point->dist_between(*second_point);
        MDB_Vector2f interval = MDB_Vector2f(
            (first_point->x - second_point->x) / (dist * 20),
            (first_point->y - second_point->y) / (dist * 20)
            );

        MDB_Point2f test_point = *first_point - interval;

        do
        {
            test_point = test_point + interval;

            in = MDB_Maths::InsideBox(test_point, rect_dims, 0);
            if (in && was_in)
            {
            }
            else if (in && !was_in)
            {
                was_in = true;
                found = true;
                *first_point = test_point;
            }
            else if (!in && was_in)
            {
                *second_point = test_point;
            }
        } while (test_point != *second_point);

        return found;
    }

    *first_point = MDB_Point2f();
    *second_point = MDB_Point2f();

    return false;
}



MDB_Vector2f MDB_Maths::SymplecticEulerIntegration(MDB_Vector2f velocity, MDB_Vector2f acceleration, float time, MDB_Vector2f &newVelocity)
{
    newVelocity = MDB_Vector2f(velocity + (acceleration * time));
    return (newVelocity * time);
}

float MDB_Maths::SymplepticEulerImpact(float elasticity, MDB_Vector2f contact_normal, MDB_Vector2f joint_velocity, float mass_a, float mass_b)
{
    return (-1 * (1 + elasticity) * joint_velocity.dot_product(contact_normal)) / (contact_normal.dot_product(contact_normal) * ((1 / mass_a) + (1 / mass_b)));
}
