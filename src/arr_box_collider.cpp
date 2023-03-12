#include "arr_box_collider.h"

namespace arr
{
    Box_Collider::Box_Collider(bn::sprite_ptr& sprite, bn::fixed width, bn::fixed height) :
        _sprite(sprite),
        _half_width(width/2),
        _half_height(height/2)
    {}

    bn::fixed   Box_Collider::origin_x()    { return _sprite.x(); }
    bn::fixed   Box_Collider::origin_y()    { return _sprite.y(); }
    bn::fixed   Box_Collider::width()       { return _half_width * 2; }
    bn::fixed   Box_Collider::height()      { return _half_height * 2; }
    bn::fixed   Box_Collider::half_width()  { return _half_width; }
    bn::fixed   Box_Collider::half_height() { return _half_height; }


    void        Box_Collider::set_sprite(bn::sprite_ptr& sprite) {
        _sprite = sprite;
    }


    bn::fixed   Box_Collider::box_projection(const bn::fixed &circle_pos, 
                            const bn::fixed &box_origin, const bn::fixed &box_half_side)
    {
        if (circle_pos < box_origin - box_half_side) 
            return box_origin - box_half_side;

        if (circle_pos > box_origin + box_half_side) 
            return box_origin + box_half_side;

        return circle_pos;
    }


    bool        Box_Collider::check_collision(Circle_Collider& circle_collider)
    {
        bn::fixed c_x = box_projection(circle_collider.origin_x(), origin_x(), _half_width);
        bn::fixed c_y = box_projection(circle_collider.origin_y(), origin_y(), _half_height);

        if ((circle_collider.origin_x() - c_x) * (circle_collider.origin_x() - c_x) +
            (circle_collider.origin_y() - c_y) * (circle_collider.origin_y() - c_y) <=
            (circle_collider.radius() * circle_collider.radius()))
        {
            on_collision();
            circle_collider.on_collision();
            return true;
        }
        return false;
    }

    bool        Box_Collider::check_collision(Box_Collider& box_collider) 
    {
        if (origin_x() - half_width()  <= box_collider.origin_x() + box_collider.half_width()  &&
            origin_x() + half_width()  >= box_collider.origin_x() - box_collider.half_width()  &&
            origin_y() - half_height() <= box_collider.origin_y() + box_collider.half_height() &&
            origin_y() + half_height() >= box_collider.origin_y() - box_collider.half_height())
        {
            on_collision();
            box_collider.on_collision();
            return true;
        }
        return false;
    }

    void        Box_Collider::on_collision() {} // virtual
}