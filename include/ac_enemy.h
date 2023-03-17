#ifndef AC_ENEMY_H
#define AC_ENEMY_H

// butano
#include "bn_sprite_ptr.h"
#include "bn_fixed_point.h"
// arr
#include "arr_circle_collider.h"

namespace ac
{
    class Enemy
    {
        public:
            Enemy();
            arr::Circle_Collider col;
            
            void init();
            void update();
            bool is_active();
            void deactivate();

        private:
            bn::sprite_ptr _sprite;
            bn::fixed_point _velocity;
            int _frames_left;
            bn::fixed _dx;
    };
}

#endif