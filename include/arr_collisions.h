#ifndef ARR_COLLISIONS_H
#define ARR_COLLISIONS_H

#include "arr_box_collider.h"
#include "arr_circle_collider.h"

namespace arr
{
    [[nodiscard]] bool check_collision(Box_Collider& box_a, Box_Collider& box_b);
    [[nodiscard]] bool check_collision(Circle_Collider& circle_a, Circle_Collider& circle_b);
    [[nodiscard]] bool check_collision(Box_Collider& box, Circle_Collider& circle);
    [[nodiscard]] bool check_collision(Circle_Collider& circle, Box_Collider& box);
}

#endif