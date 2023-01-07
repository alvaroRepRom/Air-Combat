#ifndef AC_PLAYER_H
#define AC_PLAYER_H

// butano
#include "bn_sprite_ptr.h"
// air combat
#include "ac_mode_7_camera.h"
#include "ac_plane_anim.h"

namespace ac
{
    class Player
    {
        private:      
            bn::sprite_ptr _sprite;
            Plane_Anim _player_anim;

            int _speed();

        public:
            Player(Camera& camera, bn::sprite_ptr sprite_sheet);
            Camera camera;
            void update();
    };
}

#endif