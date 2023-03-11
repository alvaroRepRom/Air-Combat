#include "arr_circle_collider.h"

namespace arr
{
    Circle_Collider::Circle_Collider(bn::sprite_ptr& sprite, bn::fixed radius) :
        _sprite(sprite),
        _radius(radius)
    {}

    bn::fixed       Circle_Collider::origin_x(){ return _sprite.x(); }
    bn::fixed       Circle_Collider::origin_y(){ return _sprite.y(); }
    bn::fixed       Circle_Collider::radius()  { return _radius; }

    void            Circle_Collider::set_sprite(bn::sprite_ptr& sprite)
    {
        _sprite = sprite;
    }

    void            Circle_Collider::on_collision()
    {

    }
}