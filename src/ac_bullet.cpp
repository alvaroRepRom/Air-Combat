#include "ac_bullet.h"
// butano
#include "bn_keypad.h"
// air combat
#include "bn_sprite_items_bullet.h"

namespace ac
{
    Bullet::Bullet() : 
        _sprite(bn::sprite_items::bullet.create_sprite(0, 0)),
        _frames_left(120) // 2 secod
    {
        _sprite.set_visible(false);
    }

    void Bullet::init(bn::fixed x_shoot_pos, bn::fixed y_shoot_pos)
    {
        _sprite.set_visible(true);
        _sprite.set_position(x_shoot_pos, y_shoot_pos);
        _frames_left = 120;
    }

    void Bullet::update()
    {
        if (bn::keypad::a_pressed() && !_sprite.visible())
        {
            init(0, 45);
        }

        if (_sprite.visible())
        {
            _sprite.set_y(_sprite.y() - 1);

            _frames_left--;
            if (_frames_left < 0)
                _sprite.set_visible(false);
        }
    }
    
    bool Bullet::is_been_used() const
    {
        return _sprite.visible();
    }
}