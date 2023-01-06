#ifndef AC_PLAYER_H
#define AC_PLAYER_H

#include "ac_mode_7_camera.h"
#include "bn_sprite_ptr.h"

namespace ac
{
    class Player
    {
        private:      
            ac::Camera _camera;
            bn::sprite_ptr _sprite; 
            int _speed();

        public:
            Player(ac::Camera& cam, bn::sprite_ptr sprite_sheet);
            void update();
    };
}

#endif