#ifndef AC_GAME_EVENTS_H
#define AC_GAME_EVENTS_H

// butano
#include "bn_array.h"
#include "bn_forward_list.h"
// air combat
#include "ac_constants.h"
// arr
#include "arr_box_collider.h"
#include "arr_circle_collider.h"

namespace ac
{
    class arr::Circle_Collider;
    
    class Game_Events
    {
        public:
            bn::array<arr::Circle_Collider*, 3> bullet_col_array;
            bn::forward_list<arr::Circle_Collider*, 3> bullet_col_f_list;
    };
}

#endif