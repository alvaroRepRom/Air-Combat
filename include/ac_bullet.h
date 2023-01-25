#ifndef AC_BULLET_H
#define AC_BULLET_H

// butano
#include "bn_sprite_ptr.h"
#include "bn_fixed_point.h"
// arr
#include "arr_circle_collider.h"

namespace ac
{
    class Bullet
    {
        public:
            Bullet();
            arr::Circle_Collider col;

            void update();
            void init(const bn::fixed_point &shoot_position, const bn::fixed_point &aimed_position);
            bool is_active() const;

        private:
            bn::sprite_ptr _sprite;
            bn::fixed_point _velocity;
            int _frames_left;
    };
}

#endif