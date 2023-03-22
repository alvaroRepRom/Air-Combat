#include "ac_enemy.h"
// butano
#include "bn_log.h"
#include "bn_math.h"
// assets
#include "bn_sprite_items_pivot.h"

namespace ac
{
    Enemy::Enemy() :
        col(_sprite, 16),
        _sprite(bn::sprite_items::pivot.create_sprite(0, 0)),
        _dx(0.5),
        _dy(0.5)
    {
        _goes_right = true;
        _goes_up = false;
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
        _sprite.set_position(_sprite.x() + _dx, _sprite.y() + _dy);
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