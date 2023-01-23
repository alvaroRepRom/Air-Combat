#include "ac_collision.h"

namespace ac
{
    [[nodiscard]] bool check_collision(Collider& box_a, Collider& box_b)
    {
        return box_a.origin_x() - box_a.width()/2  <= box_b.origin_x() + box_b.width()/2  &&
               box_a.origin_x() + box_a.width()/2  >= box_b.origin_x() - box_b.width()/2  &&
               box_a.origin_y() - box_a.height()/2 <= box_b.origin_y() + box_b.height()/2 &&
               box_a.origin_y() + box_a.height()/2 >= box_b.origin_y() - box_b.height()/2;
    }
/*
    [[nodiscard]] bool check_collision2(Collider& circle_a, Collider& circle_b)
    {
        return (circle_b.origin_x() - circle_a.origin_x()) * (circle_b.origin_x() - circle_a.origin_x()) +
               (circle_b.origin_y() - circle_a.origin_y()) * (circle_b.origin_y() - circle_a.origin_y()) <
               (circle_b.radius()   + circle_a.radius())   * (circle_b.radius()   + circle_a.radius());
    }

    [[nodiscard]] bool check_collision3(Collider& circle, Collider& box)
    {
        bn::fixed c_x = box_projection(circle.origin_x(), box.origin_x(), box.width()/2);
        bn::fixed c_y = box_projection(circle.origin_y(), box.origin_x(), box.height()/2);

        if (circle.origin_x() < box.origin_x() - box.width()/2) 
            c_x = box.origin_x() - box.width()/2;
        else 
        if (circle.origin_x() > box.origin_x() + box.width()/2) 
            c_x = box.origin_x() + box.width()/2;
        else 
            c_x = circle.origin_x();


        if (circle.origin_y() < box.origin_y() - box.height()/2) 
            c_x = box.origin_y() - box.height()/2;
        else 
        if (circle.origin_y() > box.origin_y() + box.height()/2) 
            c_x = box.origin_y() + box.height()/2;
        else 
            c_x = circle.origin_y();


        return (circle.origin_x() - c_x) * (circle.origin_x() - c_x) +
               (circle.origin_y() - c_y) * (circle.origin_y() - c_y) <
               (circle.radius() * circle.radius());
    }

    bn::fixed box_projection(const bn::fixed &c_pos, const bn::fixed &box_origin, const bn::fixed &c_half_side)
    {
        if (c_pos < box_origin - c_half_side) 
            return box_origin - c_half_side;

        if (c_pos > box_origin + c_half_side) 
            return box_origin + c_half_side;

        return c_pos;
    }*/
}