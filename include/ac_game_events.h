#ifndef AC_GAME_EVENTS_H
#define AC_GAME_EVENTS_H

// butano
#include "bn_sprite_ptr.h"
#include "bn_fixed_point.h"
#include "bn_array.h"
#include "bn_deque.h"
// air combat
#include "ac_constants.h"
// arr
#include "arr_box_collider.h"
#include "arr_circle_collider.h"
#include "arr_collisions.h"

namespace ac
{
    class arr::Circle_Collider;

    class Game_Events
    {
        public:
            bn::deque<arr::Circle_Collider, 4> bullet_col_list;
    };
}

#endif