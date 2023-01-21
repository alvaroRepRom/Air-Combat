#ifndef AC_GAME_EVENTS_H
#define AC_GAME_EVENTS_H

// butano
#include "bn_sprite_ptr.h"
#include "bn_fixed_point.h"
#include "bn_array.h"
#include "ac_collider.h"
#include "ac_constants.h"

namespace ac
{
    class Game_Events
    {
        public:
            Collider* bullet_collider;
            bn::array<Collider*, constants::NUMBER_OF_BULLETS> bullet_colliders;
    };
}

#endif