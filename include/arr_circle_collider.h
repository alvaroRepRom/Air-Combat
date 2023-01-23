#ifndef ARR_CIRCLE_COLLIDER_H
#define ARR_CIRCLE_COLLIDER_H

#include "bn_sprite_ptr.h"

namespace arr
{
    class Circle_Collider
    {
        private:
            bn::sprite_ptr _sprite;
            bn::fixed _radius;

        public:
            Circle_Collider(bn::sprite_ptr& sprite, bn::fixed radius);

            bn::fixed origin_x();
            bn::fixed origin_y();
            bn::fixed radius();

            void set_sprite(bn::sprite_ptr& sprite);
    };
}

#endif