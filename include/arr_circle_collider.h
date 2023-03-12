#ifndef ARR_CIRCLE_COLLIDER_H
#define ARR_CIRCLE_COLLIDER_H

#include "bn_sprite_ptr.h"
// arr
#include "arr_box_collider.h"

namespace arr
{
    class Box_Collider;

    class Circle_Collider
    {
        private:
            bn::sprite_ptr _sprite;
            bn::fixed _radius;

        public:
            Circle_Collider();
            Circle_Collider(bn::sprite_ptr& sprite, bn::fixed radius);

            bn::fixed origin_x();
            bn::fixed origin_y();
            bn::fixed radius();

            void set_sprite(bn::sprite_ptr& sprite);
            void set_radius(bn::fixed radius);

            bool check_collision(Circle_Collider& circle_collider);
            bool check_collision(Box_Collider& box_collider);

            virtual void on_collision();
    };
}

#endif