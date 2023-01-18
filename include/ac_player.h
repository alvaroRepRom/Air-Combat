#ifndef AC_PLAYER_H
#define AC_PLAYER_H

// butano
#include "bn_sprite_ptr.h"
// air combat
#include "ac_mode_7_camera.h"
#include "ac_plane_anim.h"
#include "ac_bullet_pool.h"
#include "ac_collider.h"
#include "ac_game_events.h"

namespace ac
{
    class Player
    {
        private:      
            bn::sprite_ptr _sprite;
            bn::sprite_ptr _aim_cross_sprite;
            Plane_Anim _player_anim;
            Bullet_Pool _bullet_pool;
            int _wait_shot_cadence;
            Game_Events* _game_events;

            void _move_aim_cross();
            void _move_air_ship();
            void _shooting();

        public:
            Player(bn::sprite_ptr& sprite_sheet, Game_Events* game_events);
            Camera camera;
            Collider collider;
            
            void update();
    };
}

#endif