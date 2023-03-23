#include "ac_enemy.h"
// butano
#include "bn_log.h"
#include "bn_sprite_actions.h"

namespace ac
{
    namespace {
        constexpr const bn::fixed COLLIDER_RADIUS = 9;
    }

    Enemy::Enemy(bn::sprite_ptr sprite, Game_Events* game_events) :
        arr::Circle_Collider(sprite, COLLIDER_RADIUS),
        _sprite(sprite),
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
        if (_sprite.y() > 30) {
            _goes_up = true;
        }
        else if (_sprite.y() < -30) {
            _goes_up = false;
        }

        if (_sprite.x() > 50) {
            _goes_right = false;
        }
        else if (_sprite.x() < -50) {
            _goes_right = true;
        }

        bn::fixed _dx = 1;
        bn::fixed _dy = 1;

        if (_goes_up) {
            _dy = -1;
        }
        if (!_goes_right) {
            _dx = -1;
        }
        
        bn::sprite_move_by_action move_sprite_action(_sprite, _dx, _dy);
        move_sprite_action.update();
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