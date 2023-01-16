#include "arr_box_collider.h"
#include "bn_fixed_point.h"
#include "bn_fixed.h"

namespace arr
{
    Box_Collider::Box_Collider(bn::fixed_point origin, bn::fixed width, bn::fixed height):
                    _origin(origin),
                    _width(width),
                    _height(height)
    {}

    Box_Collider::Box_Collider(bn::fixed x, bn::fixed y, bn::fixed width, bn::fixed height):
                    _origin(x, y),
                    _width(width),
                    _height(height)
    {}
    Box_Collider::Box_Collider(bn::sprite_ptr& sprite, bn::fixed width, bn::fixed height):
                    _origin(sprite.position()),
                    _width(width),
                    _height(height)
    {}

    Box_Collider::~Box_Collider(){}

//Getter
    bn::fixed_point Box_Collider::origin()  { return _origin; }
    bn::fixed       Box_Collider::origin_x(){ return _origin.x(); }
    bn::fixed       Box_Collider::origin_y(){ return _origin.y(); }
    bn::fixed       Box_Collider::width()   { return _width; }
    bn::fixed       Box_Collider::height()  { return _height; }
//Setter
    void Box_Collider::set_origin  (bn::fixed_point origin){ _origin = origin; }
    void Box_Collider::set_origin_x(bn::fixed x)           { _origin.set_x(x); }
    void Box_Collider::set_origin_y(bn::fixed y)           { _origin.set_y(y); }
    void Box_Collider::set_width   (bn::fixed width)       { _width = width; }
    void Box_Collider::set_height  (bn::fixed height)      { _height = height; }
}