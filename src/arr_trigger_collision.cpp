#include "arr_trigger_collision.h"

namespace arr
{
    [[nodiscard]] bool check_collision(Box_Collider& box_a, Box_Collider& box_b)
    {
        return box_a.origin_x() - box_a.width()/2  <= box_b.origin_x() + box_b.width()/2  &&
               box_a.origin_x() + box_a.width()/2  >= box_b.origin_x() - box_b.width()/2  &&
               box_a.origin_y() - box_a.height()/2 <= box_b.origin_y() + box_b.height()/2 &&
               box_a.origin_y() + box_a.height()/2 >= box_b.origin_y() - box_b.height()/2;
    }
}