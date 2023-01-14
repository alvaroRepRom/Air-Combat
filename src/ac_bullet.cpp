#include "ac_bullet.h"
// butano
// air combat
#include "bn_sprite_items_bullet.h"

namespace ac
{
    namespace
    {
        constexpr int WAIT_FRAMES_CADENCE = 120; // 2 secod
    }

    Bullet::Bullet() : 
        _sprite(bn::sprite_items::bullet.create_sprite(0, 0)),
        _frames_left(WAIT_FRAMES_CADENCE) 
    {
        _sprite.set_visible(false);
    }

    void Bullet::init(bn::fixed_point shoot_position)
    {
        _sprite.set_visible(true);
        _sprite.set_position(shoot_position);
        _frames_left = WAIT_FRAMES_CADENCE;
    }

    void Bullet::update()
    {
        _sprite.set_y(_sprite.y() - 1);

        _frames_left--;
        if (_frames_left < 0)
            _sprite.set_visible(false);
    }
    
    bool Bullet::is_active() const
    {
        return _sprite.visible();
    }
}