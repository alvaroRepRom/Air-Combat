#ifndef AC_BULLET_H
#define AC_BULLET_H

// butano
#include "bn_sprite_ptr.h"
#include "bn_fixed_point.h"

namespace ac
{
    class Bullet
    {
        public:
            Bullet();
            void update();
            void init(bn::fixed_point &shoot_position, bn::fixed_point &aimed_position);
            bool is_active() const;

        private:
            bn::sprite_ptr _sprite;
            bn::fixed_point _velocity;
            int _frames_left;
    };
}

#endif