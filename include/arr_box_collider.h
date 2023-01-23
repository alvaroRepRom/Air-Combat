#ifndef ARR_BOX_COLLIDER_H
#define ARR_BOX_COLLIDER_H

#include "bn_sprite_ptr.h"

namespace arr
{
    class Box_Collider
    {
        private:
            bn::sprite_ptr _sprite;
            bn::fixed _width;
            bn::fixed _height;
            bn::fixed _half_width;
            bn::fixed _half_height;

        public:
            Box_Collider(bn::sprite_ptr& sprite, bn::fixed width, bn::fixed height);

            bn::fixed origin_x();
            bn::fixed origin_y();
            bn::fixed width();
            bn::fixed height();
            bn::fixed half_width();
            bn::fixed half_height();

            void set_sprite(bn::sprite_ptr& sprite);
    };
}

#endif