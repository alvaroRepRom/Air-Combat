#include "arr_box_collider.h"

namespace arr
{
    Box_Collider::Box_Collider(bn::sprite_ptr& sprite, bn::fixed width, bn::fixed height) :
        _sprite(sprite),
        _width(width),
        _height(height),
        _half_width(width/2),
        _half_height(height/2)
    {}

    bn::fixed       Box_Collider::origin_x()   { return _sprite.x(); }
    bn::fixed       Box_Collider::origin_y()   { return _sprite.y(); }
    bn::fixed       Box_Collider::width()      { return _width; }
    bn::fixed       Box_Collider::height()     { return _height; }
    bn::fixed       Box_Collider::half_width() { return _half_width; }
    bn::fixed       Box_Collider::half_height(){ return _half_height; }

    void            Box_Collider::set_sprite(bn::sprite_ptr& sprite)
    {
        _sprite = sprite;
    }
}