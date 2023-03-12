#ifndef ARR_BOX_COLLIDER_H
#define ARR_BOX_COLLIDER_H

#include "bn_sprite_ptr.h"
// arr
#include "arr_circle_collider.h"

namespace arr
{
    class Circle_Collider;

    class Box_Collider
    {
        private:
            bn::sprite_ptr _sprite;
            bn::fixed _half_width;
            bn::fixed _half_height;
            bool _is_enabled;

        public:
            Box_Collider(bn::sprite_ptr& sprite, bn::fixed width, bn::fixed height);

            bn::fixed origin_x();
            bn::fixed origin_y();
            bn::fixed width();
            bn::fixed height();
            bn::fixed half_width();
            bn::fixed half_height();
            bool is_enabled();

            void set_sprite(bn::sprite_ptr& sprite);
            void set_enabled(bool is_enabled);

            bool check_collision(Circle_Collider& circle_collider);
            bool check_collision(Box_Collider& box_collider);

            virtual void on_collision();
    };
}

#endif