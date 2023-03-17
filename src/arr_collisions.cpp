#include "arr_collisions.h"

namespace arr
{
    namespace
    {
        bn::fixed box_projection(const bn::fixed &circle_pos, 
                                const bn::fixed &box_origin, const bn::fixed &box_half_side)
        {
            if (circle_pos < box_origin - box_half_side) 
                return box_origin - box_half_side;

            if (circle_pos > box_origin + box_half_side) 
                return box_origin + box_half_side;

            return circle_pos;
        }
    }
    /**
     * @brief Return if two box colliders has intersect.
     */
    [[nodiscard]] bool check_collision(Box_Collider& box_a, Box_Collider& box_b)
    {
        return box_a.origin_x() - box_a.half_width()  <= box_b.origin_x() + box_b.half_width()  &&
               box_a.origin_x() + box_a.half_width()  >= box_b.origin_x() - box_b.half_width()  &&
               box_a.origin_y() - box_a.half_height() <= box_b.origin_y() + box_b.half_height() &&
               box_a.origin_y() + box_a.half_height() >= box_b.origin_y() - box_b.half_height();
    }
    /**
     * @brief Return if two circle colliders has intersect.
     */
    [[nodiscard]] bool check_collision(Circle_Collider& circle_a, Circle_Collider& circle_b)
    {
        if (!circle_a.is_collision_enabled() || 
            !circle_b.is_collision_enabled()) 
            return false;
        return (circle_b.origin_x() - circle_a.origin_x()) * (circle_b.origin_x() - circle_a.origin_x()) +
               (circle_b.origin_y() - circle_a.origin_y()) * (circle_b.origin_y() - circle_a.origin_y()) <=
               (circle_b.radius()   + circle_a.radius())   * (circle_b.radius()   + circle_a.radius());
    }
    /**
     * @brief Return if a box collider and a circle collider has intersect.
     */
    [[nodiscard]] bool check_collision(Box_Collider& box, Circle_Collider& circle)
    {
        bn::fixed c_x = box_projection(circle.origin_x(), box.origin_x(), box.half_width());
        bn::fixed c_y = box_projection(circle.origin_y(), box.origin_y(), box.half_height());

        return (circle.origin_x() - c_x) * (circle.origin_x() - c_x) +
               (circle.origin_y() - c_y) * (circle.origin_y() - c_y) <=
               (circle.radius() * circle.radius());
    }
    /**
     * @brief Return if a circle collider and a box collider has intersect.
     */
    [[nodiscard]] bool check_collision(Circle_Collider& circle, Box_Collider& box)
    {
        bn::fixed c_x = box_projection(circle.origin_x(), box.origin_x(), box.half_width());
        bn::fixed c_y = box_projection(circle.origin_y(), box.origin_y(), box.half_height());

        return (circle.origin_x() - c_x) * (circle.origin_x() - c_x) +
               (circle.origin_y() - c_y) * (circle.origin_y() - c_y) <=
               (circle.radius() * circle.radius());
    }
}