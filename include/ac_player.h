#ifndef AC_PLAYER_H
#define AC_PLAYER_H

// butano
#include "bn_sprite_ptr.h"
// air combat
#include "ac_mode_7_camera.h"
#include "ac_plane_anim.h"
#include "ac_bullet_pool.h"

namespace ac
{
    class Player
    {
        private:      
            bn::sprite_ptr _sprite;
            Plane_Anim _player_anim;
            Bullet_Pool _bullet_pool;
            int _wait_shot_cadence;

            int _speed();

        public:
            Player(bn::sprite_ptr& sprite_sheet);
            Camera camera;
            
            void update();
    };
}

#endif