#ifndef AC_ENEMY_H
#define AC_ENEMY_H

// butano
#include "bn_sprite_ptr.h"
#include "bn_fixed_point.h"

namespace ac
{
    class Enemy
    {
        public:
            Enemy();
            void init();
            void update();
            bool is_active();

        private:
            bn::sprite_ptr _sprite;
            bn::fixed_point _velocity;
            int _frames_left;
    };
}

#endif