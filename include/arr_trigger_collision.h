#ifndef ARR_TRIGGER_COLLISION_H
#define ARR_TRIGGER_COLLISION_H

#include "arr_box_collider.h"

namespace arr
{
    [[nodiscard]] bool check_collision(Box_Collider& box_a, Box_Collider& box_b);
}

#endif