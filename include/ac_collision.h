#ifndef AC_COLLISION_H
#define AC_COLLISION_H

#include "ac_collider.h"

namespace ac
{
    [[nodiscard]] bool check_collision(Collider& box_a, Collider& box_b);
    [[nodiscard]] bool check_collision2(Collider& circle_a, Collider& circle_b);
    [[nodiscard]] bool check_collision3(Collider& circle, Collider& box);
}

#endif