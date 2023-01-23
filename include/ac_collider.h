#ifndef AC_COLLIDER_H
#define AC_COLLIDER_H

#include "bn_fixed_point.h"
#include "bn_sprite_ptr.h"

namespace ac
{
    class Collider
    {
        private:
            bn::sprite_ptr _sprite;
            //bn::fixed _radius;
            bn::fixed _width;
            bn::fixed _height;

        public:
            //Collider(bn::sprite_ptr& sprite, bn::fixed radius);
            Collider(bn::sprite_ptr& sprite, bn::fixed width, bn::fixed height);

            bn::fixed origin_x();
            bn::fixed origin_y();
            bn::fixed width();
            bn::fixed height();
            //bn::fixed radius();

            void set_sprite(bn::sprite_ptr& sprite);

            [[nodiscard]] bool check_collision(Collider& box_b);
    };
}

#endif