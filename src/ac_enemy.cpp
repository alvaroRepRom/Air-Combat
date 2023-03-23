#include "ac_enemy.h"
// butano
#include "bn_log.h"
#include "bn_math.h"

namespace ac
{
    namespace {
        constexpr const bn::fixed COLLIDER_RADIUS = 9;
    }

    Enemy::Enemy(bn::sprite_ptr sprite, Game_Events* game_events) :
        arr::Circle_Collider(sprite, COLLIDER_RADIUS),
        _sprite(sprite),
        _dx(0.5),
        _dy(0.5),
        _game_events(game_events)
    {
        _goes_right = true;
        _goes_up = false;
        _sprite.set_visible(false);
        _sprite.set_z_order(1);
    }

    void Enemy::init()
    {
        _sprite.set_visible(true);
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

    void Enemy::on_collision() 
    {
        deactivate();
    }
}