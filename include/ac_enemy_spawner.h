#ifndef AC_ENEMY_SPAWNER_H
#define AC_ENEMY_SPAWNER_H

// butano
#include "bn_sprite_ptr.h"
#include "bn_array.h"
#include "bn_fixed_point.h"
#include "bn_random.h"
// air combat
#include "ac_enemy.h"
#include "ac_game_events.h"

namespace ac
{
    class Enemy;

    class Enemy_Spawner
    {
        public:
            Enemy_Spawner(Game_Events* game_events);
            void update();

        private:
            bn::array<Enemy, 3> _enemy_pool;
            bn::random _random_generator;
            int _frames_left;
            Game_Events* _game_events;

            void spawn();
    };
}

#endif