#ifndef ARR_BOX_COLLIDER_H
#define ARR_BOX_COLLIDER_H

#include "bn_fixed.h"
#include "bn_fixed_point.h"
#include "bn_sprite_ptr.h"
#include "intellisense.h"

namespace arr
{
    class Box_Collider
    {
        private:
            bn::fixed_point _origin;
            bn::fixed _width;
            bn::fixed _height;

        public:
            Box_Collider();
            Box_Collider(bn::fixed_point origin, bn::fixed width, bn::fixed height);
            Box_Collider(bn::fixed x, bn::fixed y, bn::fixed width, bn::fixed height);
            Box_Collider(bn::sprite_ptr& sprite, bn::fixed width, bn::fixed height);
            ~Box_Collider();

            bn::fixed_point origin();
            bn::fixed origin_x();
            bn::fixed origin_y();
            bn::fixed width();
            bn::fixed height();

            void set_origin(bn::fixed_point origin);
            void set_origin_x(bn::fixed x);
            void set_origin_y(bn::fixed y);
            void set_width(bn::fixed width);
            void set_height(bn::fixed height);
    };
}

#endif