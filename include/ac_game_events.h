#ifndef AC_GAME_EVENTS_H
#define AC_GAME_EVENTS_H

// butano
#include "bn_sprite_ptr.h"
#include "bn_fixed_point.h"
#include "ac_collider.h"

namespace ac
{
    struct Game_Events
    {
        Collider* bullet_collider;
    };
}

#endif