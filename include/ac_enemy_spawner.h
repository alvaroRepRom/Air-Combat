#ifndef AC_ENEMY_SPAWNER_H
#define AC_ENEMY_SPAWNER_H

// butano
#include "bn_array.h"
#include "bn_random.h"
#include "bn_fixed_point.h"
// air combat
#include "ac_enemy.h"
#include "ac_game_events.h"
#include "ac_constants.h"

namespace ac
{
    class Enemy;
    class Game_events;

    class Enemy_Spawner
    {
        public:
            Enemy_Spawner(Game_Events* game_events);
            void update();

        private:
            bn::array<Enemy, constants::NUMBER_OF_ENEMIES> _enemy_array;            
            bn::random _random_generator;
            int _frames_left;
            Game_Events* _game_events;
            int _next_enemy_index;
            
            void _spawn();
    };
}

#endif