#include "ac_enemy.h"
// butano
#include "bn_math.h"
// assets
#include "bn_sprite_items_pivot.h"

namespace ac
{
    Enemy::Enemy() :
        _sprite(bn::sprite_items::pivot.create_sprite(0, 0)),
        col(_sprite, 16),
        _dx(0.5)
    {
        _sprite.set_visible(false);
        _sprite.set_z_order(1);
    }

    void Enemy::init()
    {
        _sprite.set_visible(true);
        col.set_sprite(_sprite);
        _sprite.set_position(0, 0);
    }

    void Enemy::update()
    {        
        _sprite.set_x(_sprite.x() + _dx);
        if (bn::abs(_sprite.x()) > 20)
            _dx *= -1;
    }

    bool Enemy::is_active()
    {
        return _sprite.visible();
    }

    void Enemy::deactivate()
    {
        _sprite.set_visible(false);
    }
}