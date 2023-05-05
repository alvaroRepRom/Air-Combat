#include "ac_enemy.h"
// butano
#include "bn_log.h"
#include "bn_sprite_actions.h"
// assets
#include "bn_sprite_items_explosion.h"

namespace ac
{
    namespace {
        constexpr const bn::fixed COLLIDER_RADIUS = 9;
        constexpr const int HALF_WIDTH = 100;
        constexpr const int HALF_HEIGHT = 60;
    }

    Enemy::Enemy(bn::sprite_ptr sprite, Game_Events* game_events) :
        arr::Circle_Collider(sprite, COLLIDER_RADIUS),
        _sprite(sprite),
        _explosion_sprite(bn::sprite_items::explosion.create_sprite(0, 0)),
        _explosion_action(bn::create_sprite_animate_action_forever(_explosion_sprite, 20, 
                        bn::sprite_items::explosion.tiles_item(), 0, 1, 2, 3)),
        _game_events(game_events)
    {
        _goes_right = true;
        _goes_up = false;
        _is_exploded = false;
        _sprite.set_visible(false);
        _sprite.set_z_order(1);
        _explosion_sprite.set_visible(false);
    }

    void Enemy::init()
    {
        _sprite.set_visible(true);
        _sprite.set_position(0, 0);
        set_collision_enabled(true);
    }

    void Enemy::update()
    {
        if (_is_exploded) 
        {
            _explosion_action.update();
        }
        else
        {
            if (_sprite.y() > HALF_HEIGHT) {
                _goes_up = true;
            }
            else if (_sprite.y() < -HALF_HEIGHT) {
                _goes_up = false;
            }

            if (_sprite.x() > HALF_WIDTH) {
                _goes_right = false;
            }
            else if (_sprite.x() < -HALF_WIDTH) {
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
        
    }

    bool Enemy::is_active()
    {
        return _sprite.visible() || _explosion_sprite.visible();
    }

    void Enemy::deactivate() 
    {
        _sprite.set_visible(false);
    }

    void Enemy::on_collision() 
    {
        set_collision_enabled(false);
        _explosion_sprite.set_visible(true);
        _explosion_sprite.set_position(_sprite.position());
        _sprite.set_visible(false);
        _is_exploded = true;
    }
}