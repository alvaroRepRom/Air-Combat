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
    class arr::Circle_Collider;
    
    class Game_Events
    {
        public:
            bn::forward_list<arr::Circle_Collider*, ac::constants::NUMBER_OF_BULLETS> bullet_col_f_list;
            bool has_change_score;
            int score;
    };
}

#endif