#include "arr_circle_collider.h"

namespace arr
{
    Circle_Collider::Circle_Collider(bn::sprite_ptr& sprite, bn::fixed radius) :
        _sprite(sprite),
        _radius(radius),
        _is_enabled(true)
    {}

// Getters
    bn::fixed   Circle_Collider::origin_x()   { return _sprite.x(); }
    bn::fixed   Circle_Collider::origin_y()   { return _sprite.y(); }
    bn::fixed   Circle_Collider::radius()     { return _radius; }
    bool        Circle_Collider::is_collision_enabled() { return _is_enabled; }

// Setters
    void        Circle_Collider::set_sprite(bn::sprite_ptr& sprite) {
        _sprite = sprite;
    }

    void        Circle_Collider::set_radius(bn::fixed radius) {
        _radius = radius;
    }

    void        Circle_Collider::set_collision_enabled(bool is_collision_enabled) {
        _is_enabled = is_collision_enabled;
    }

// Methods
    bool        Circle_Collider::check_collision(Circle_Collider& circle_collider){
        if (_is_enabled && circle_collider.is_collision_enabled())
        {
            if ((circle_collider.origin_x() - origin_x()) * (circle_collider.origin_x() - origin_x()) +
                (circle_collider.origin_y() - origin_y()) * (circle_collider.origin_y() - origin_y()) <=
                (circle_collider.radius()   + radius())   * (circle_collider.radius()   + radius()))
            {
                on_collision();
                circle_collider.on_collision();
                return true;
            }
        }        
        return false;
    }

    bool        Circle_Collider::check_collision(Box_Collider& box_collider) {
        return box_collider.check_collision(*this);
    }

// Virtual
    void        Circle_Collider::on_collision() {}
}