#include "arr_circle_collider.h"

namespace arr
{
    Circle_Collider::Circle_Collider(bn::sprite_ptr& sprite, bn::fixed radius) :
        _sprite(sprite),
        _radius(radius)
    {}


    bn::fixed   Circle_Collider::origin_x() { return _sprite.x(); }
    bn::fixed   Circle_Collider::origin_y() { return _sprite.y(); }
    bn::fixed   Circle_Collider::radius()   { return _radius; }


    void        Circle_Collider::set_sprite(bn::sprite_ptr& sprite) {
        _sprite = sprite;
    }

    void        Circle_Collider::set_radius(bn::fixed radius) {
        _radius = radius;
    }


    bool        Circle_Collider::check_collision(Circle_Collider& circle_collider){
        if ((circle_collider.origin_x() - origin_x()) * (circle_collider.origin_x() - origin_x()) +
            (circle_collider.origin_y() - origin_y()) * (circle_collider.origin_y() - origin_y()) <=
            (circle_collider.radius()   + radius())   * (circle_collider.radius()   + radius()))
        {
            on_collision();
            circle_collider.on_collision();
            return true;
        }
        return false;
    }

    bool        Circle_Collider::check_collision(Box_Collider& box_collider) {
        bn::fixed c_x = box_collider.box_projection(origin_x(), box_collider.origin_x(), box_collider.half_width());
        bn::fixed c_y = box_collider.box_projection(origin_y(), box_collider.origin_y(), box_collider.half_height());

        if ((origin_x() - c_x) * (origin_x() - c_x) +
            (origin_y() - c_y) * (origin_y() - c_y) <=
            (_radius * _radius))
        {
            on_collision();
            box_collider.on_collision();
            return true;
        }
        return false;
    }

    void        Circle_Collider::on_collision() {} // virtual
}