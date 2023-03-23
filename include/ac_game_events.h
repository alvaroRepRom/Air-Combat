#ifndef AC_GAME_EVENTS_H
#define AC_GAME_EVENTS_H

// butano
#include "bn_forward_list.h"
// air combat
#include "ac_constants.h"
// arr
#include "arr_circle_collider.h"

namespace ac
{
    class Game_Events
    {
        public:
            Game_Events() { bullet_col_f_list.clear(); score = 0; }
            bn::forward_list<arr::Circle_Collider*, ac::constants::NUMBER_OF_BULLETS> bullet_col_f_list;
            int score;
    };
}

#endif