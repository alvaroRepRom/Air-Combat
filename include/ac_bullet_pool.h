#ifndef AC_BULLET_POOL_H
#define AC_BULLET_POOL_H

// butano
#include "bn_sprite_ptr.h"
#include "bn_array.h"
#include "bn_fixed_point.h"
// air combat
#include "ac_bullet.h"

namespace ac
{
    class Bullet_Pool
    {
        public:
            Bullet_Pool();
            void shoot_bullet(bn::fixed_point shoot_position, bn::fixed_point aimed_position);
            void update();

        private:
            bn::array<Bullet, 3> _pool;
    };
}

#endif