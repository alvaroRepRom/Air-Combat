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

    [[nodiscard]] bool Collider::check_collision(Collider& box_b)
    {
        return this->origin_x() - this->width()/2  <= box_b.origin_x() + box_b.width()/2  &&
               this->origin_x() + this->width()/2  >= box_b.origin_x() - box_b.width()/2  &&
               this->origin_y() - this->height()/2 <= box_b.origin_y() + box_b.height()/2 &&
               this->origin_y() + this->height()/2 >= box_b.origin_y() - box_b.height()/2;
    }
}