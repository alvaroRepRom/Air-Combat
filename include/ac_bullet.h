#ifndef AC_BULLET_H
#define AC_BULLET_H

// butano
#include "bn_sprite_ptr.h"
// air combat

namespace ac
{
    class Bullet
    {
        public:
            Bullet();
            void update();
            void init(bn::fixed x_shoot_pos, bn::fixed y_shoot_pos);
            bool is_been_used() const;

        private:
            bn::sprite_ptr _sprite;
            int _frames_left;
    };
}

#endif