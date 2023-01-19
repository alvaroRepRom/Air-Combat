#include "ac_collider.h"

namespace ac
{
    Collider::Collider(bn::sprite_ptr& sprite, bn::fixed width, bn::fixed height) :
        _sprite(sprite),
        _width(width),
        _height(height)
    {}

    bn::fixed       Collider::origin_x(){ return _sprite.x(); }
    bn::fixed       Collider::origin_y(){ return _sprite.y(); }
    bn::fixed       Collider::width()   { return _width; }
    bn::fixed       Collider::height()  { return _height; }

    void            Collider::set_sprite(bn::sprite_ptr& sprite)
    {
        _sprite = sprite;
    }

    [[nodiscard]] 
    bool            Collider::check_collision(Collider& box_b)
    {
        return origin_x() - width()/2  <= box_b.origin_x() + box_b.width()/2  &&
               origin_x() + width()/2  >= box_b.origin_x() - box_b.width()/2  &&
               origin_y() - height()/2 <= box_b.origin_y() + box_b.height()/2 &&
               origin_y() + height()/2 >= box_b.origin_y() - box_b.height()/2;
    }
}