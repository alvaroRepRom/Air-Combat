#ifndef AC_BULLET_POOL_H
#define AC_BULLET_POOL_H

// butano
#include "bn_sprite_ptr.h"
#include "bn_array.h"
#include "bn_fixed_point.h"
// air combat
#include "ac_bullet.h"
#include "ac_game_events.h"

namespace ac
{
    class Bullet_Pool
    {
        public:
            Bullet_Pool(Game_Events* game_events);
            void shoot_bullet(const bn::fixed_point &shoot_position, const bn::fixed_point &aimed_position);
            void update();

        private:
            bn::array<Bullet, 1> _pool;
            Game_Events* _game_events;
    };
}

#endif