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

    Enemy::Enemy(bn::sprite_ptr sprite, Game_Events* game_events, Enemy_Type enemy_type) :
        arr::Circle_Collider(sprite, COLLIDER_RADIUS),
        _sprite(sprite),
        _explosion_sprite(bn::sprite_items::explosion.create_sprite(0, 0)),
        _explosion_action(bn::create_sprite_animate_action_once(_explosion_sprite, 10, 
                        bn::sprite_items::explosion.tiles_item(), 0, 1, 2, 3)),
        _game_events(game_events),
        _enemy_type(enemy_type)
    {
        _goes_right = true;
        _goes_up = false;
        _sprite.set_visible(false);
        _sprite.set_z_order(1);
        _explosion_sprite.set_visible(false);
    }

    void Enemy::init()
    {
        _sprite.set_visible(true);

        switch (_enemy_type)
        {
        case Enemy_Type::Type_2:
            _rand.update();
            break;
        case Enemy_Type::Type_3:
            _rand.update();
            _rand.update();
        default: break;
        }
        
        int x = _rand.get_int(-HALF_WIDTH + 10, HALF_WIDTH - 10);
        int y = _rand.get_int(-HALF_HEIGHT + 10, HALF_HEIGHT - 10);
        _sprite.set_position(x, y);

        set_collision_enabled(true);
    }

    void Enemy::update()
    {
        if (_explosion_sprite.visible()) 
        {
            if (_explosion_action.done()) {
                _explosion_sprite.set_visible(false);
            }
            else {
                _explosion_action.update();
            }
        }
        else
        {
            bn::fixed _dx = 1;
            bn::fixed _dy = 1;

            switch (_enemy_type)
            {
            case Enemy_Type::Type_1:

                if (_sprite.y() > HALF_HEIGHT) {
                _goes_up = true;
                }
                else if (_sprite.y() < -HALF_HEIGHT) {
                    _goes_up = false;
                }

                if (_sprite.x() > HALF_WIDTH) {
                    _goes_right = false;
                    _rand.update();
                }
                else if (_sprite.x() < -HALF_WIDTH) {
                    _goes_right = true;
                }

                if (!_goes_right) {
                    _dx = -2;
                }
                else {
                    _dx = 2;
                }
                _dy = 0;

                break;

            case Enemy_Type::Type_2: 

                if (_sprite.y() > HALF_HEIGHT) {
                    _goes_up = true;
                    _rand.update();
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

                if (_goes_up) {
                    _dy = -1;
                }
                if (!_goes_right) {
                    _dx = -1;
                }

                break;

            case Enemy_Type::Type_3:

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
                    _rand.update();
                }                

                if (_goes_up) {
                    _dy = -1;
                }
                if (!_goes_right) {
                    _dx = -1;
                    _rand.update();
                }

                break;

            default: BN_ERROR("Invalid enemy type: ", _enemy_type);
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

    int Enemy::score_given() 
    {
        switch (_enemy_type)
        {
        case Enemy_Type::Type_1: return 5;
        case Enemy_Type::Type_2: return 10;
        case Enemy_Type::Type_3: return 15;
        default: return 0;
        }
    }

    void Enemy::on_collision() 
    {
        set_collision_enabled(false);
        _explosion_sprite.set_visible(true);
        _explosion_sprite.set_position(_sprite.position());
        _explosion_action.reset();
        _sprite.set_visible(false);
    }
}