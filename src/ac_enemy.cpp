#include "ac_enemy.h"
// assets
#include "bn_sprite_items_pivot.h"

namespace ac
{
    Enemy::Enemy() :
        _sprite(bn::sprite_items::pivot.create_sprite(0, 0))
    {
        _sprite.set_visible(false);
        _sprite.set_z_order(1);
    }

    void Enemy::init()
    {
        _sprite.set_visible(true);
    }

    void Enemy::update()
    {

    }

    bool Enemy::is_active()
    {
        return _sprite.visible();
    }
}