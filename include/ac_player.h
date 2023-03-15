#ifndef AC_PLAYER_H
#define AC_PLAYER_H

// butano
#include "bn_sprite_ptr.h"
#include "bn_array.h"
// air combat
#include "ac_bullet.h"
#include "ac_game_events.h"
#include "ac_constants.h"

namespace ac
{
    class Player
    {
        private:      
            bn::sprite_ptr _sprite;
            bn::sprite_ptr _aim_cross_sprite;
            int _wait_shot_cadence;
            bn::array<Bullet, ac::constants::NUMBER_OF_BULLETS> _bullet_array;

            void _move_aim_cross();
            void _move_air_ship();
            void _shooting();

        public:
            Player(bn::sprite_ptr& sprite_sheet, Game_Events* game_events);

            void update();
    };
}

#endif