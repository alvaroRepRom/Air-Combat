#include "ac_player.h"
// butano
#include "bn_math.h"
#include "bn_display.h"
#include "bn_keypad.h"
#include "bn_log.h"
// air combat
#include "bn_sprite_items_cross.h"
#include "bn_sprite_items_plane_sheet.h"

namespace ac
{
    namespace
    {
        constexpr const int WAIT_SHOT_CADENCE = 15;
        constexpr const int X_BORDER = bn::display::width() / 2 - 20;
        constexpr const int Y_BORDER = bn::display::height() / 2 - 20;
        constexpr const bn::fixed_point AIM_OFFSET(30, 15);
        constexpr const int INIT_Y = 48;
    }

    Player::Player(bn::sprite_ptr& sprite_sheet, Game_Events* game_events) : 
        _sprite(sprite_sheet),
        _aim_cross_sprite(bn::sprite_items::cross.create_sprite(0, 0)),
        _player_anim(_sprite),
        _bullet_pool(game_events),
        _wait_shot_cadence(WAIT_SHOT_CADENCE),
        _game_events(game_events),
        collider(_sprite, 32, 14)
    {
        _sprite.set_position(0, INIT_Y);
    }

    void Player::update()
    {       
        _move_aim_cross();
        _move_air_ship();
        _shooting();
        //BN_LOG("collider position: ", collider.origin_x(), ", ", collider.origin_y());
    }

    void Player::_move_aim_cross()
    {
        // turn left and right
        if(bn::keypad::left_held())
        {
            _aim_cross_sprite.set_x(_aim_cross_sprite.x() - 1);
            if (_aim_cross_sprite.x() < -X_BORDER)
                _aim_cross_sprite.set_x(-X_BORDER);
        }
        else if(bn::keypad::right_held())
        {
            _aim_cross_sprite.set_x(_aim_cross_sprite.x() + 1);
            if (_aim_cross_sprite.x() > X_BORDER)
                _aim_cross_sprite.set_x(X_BORDER);
        }
        else // if not X-axis input, go to ship X position
        {
            if (_aim_cross_sprite.x() > _sprite.x())
            {
                _aim_cross_sprite.set_x(_aim_cross_sprite.x() - 1);
            }
            else if (_aim_cross_sprite.x() < _sprite.x())
            {
                _aim_cross_sprite.set_x(_aim_cross_sprite.x() + 1);
            }
        }
        
        // up and down
        if(bn::keypad::down_held())
        {
            _aim_cross_sprite.set_y(_aim_cross_sprite.y() + 1);
            if (_aim_cross_sprite.y() > Y_BORDER - INIT_Y + AIM_OFFSET.y())
                _aim_cross_sprite.set_y(Y_BORDER - INIT_Y + AIM_OFFSET.y());
        }
        else if(bn::keypad::up_held())
        {
            _aim_cross_sprite.set_y(_aim_cross_sprite.y() - 1);
            if (_aim_cross_sprite.y() < -Y_BORDER)
                _aim_cross_sprite.set_y(-Y_BORDER);
        }
        else // if not Y-axis input, go to ship Y position
        {
            if (_aim_cross_sprite.y() > _sprite.y() - INIT_Y)
            {
                _aim_cross_sprite.set_y(_aim_cross_sprite.y() - 1);
            }
            else if (_aim_cross_sprite.y() < _sprite.y() - INIT_Y)
            {
                _aim_cross_sprite.set_y(_aim_cross_sprite.y() + 1);
            }
        }
    }

    void Player::_move_air_ship()
    {
        int sprite_index = 0;
        // MOVE SHIP X
        bn::fixed x_dist = _aim_cross_sprite.x() - _sprite.x();        
        if (x_dist > 0) // IF aim to the right
        {
            sprite_index = 1;
            bn::fixed delta_x = 0.5;
            if (x_dist > AIM_OFFSET.x())
            {
                sprite_index = 2;
                delta_x = 1;
            }

            if(_sprite.x() < X_BORDER - AIM_OFFSET.x())
                _sprite.set_x(_sprite.x() + delta_x);
        }
        else 
        if (x_dist < 0) // IF aim to the left
        {
            sprite_index = 5;
            bn::fixed delta_x = 0.5;
            if (x_dist < -AIM_OFFSET.x())
            {
                sprite_index = 6;
                delta_x = 1;
            }

            if(_sprite.x() > -X_BORDER + AIM_OFFSET.x())
                _sprite.set_x(_sprite.x() - delta_x);
        }

        // MOVE SHIP Y
        bn::fixed y_dist = _aim_cross_sprite.y() - _sprite.y() + INIT_Y;
        if (y_dist > 0) // aim down
        {
            bn::fixed delta_y = 0.5;
            if (y_dist > AIM_OFFSET.y())
            {
                delta_y = 1;
            }
            _sprite.set_y(_sprite.y() + delta_y);

            // STOP DOWN ship movement 
            if (_sprite.y() > Y_BORDER)
                _sprite.set_y(Y_BORDER);
        }
        else 
        if (y_dist < 0) // aim up
        {
            bn::fixed delta_y = 0.5;
            if (y_dist < -AIM_OFFSET.y())
            {
                delta_y = 1;
            }
            _sprite.set_y(_sprite.y() - delta_y);

            // STOP UP ship movement 
            if (_sprite.y() < -Y_BORDER + INIT_Y + AIM_OFFSET.y())
                _sprite.set_y(-Y_BORDER + INIT_Y + AIM_OFFSET.y());
        }

        _sprite.set_item(bn::sprite_items::plane_sheet, sprite_index);
    }

    void Player::_shooting()
    {
        _bullet_pool.update(); // update active bullets

        _wait_shot_cadence--;
        if (bn::keypad::a_held() && _wait_shot_cadence < 0)
        {
            _bullet_pool.shoot_bullet(_sprite.position(), _aim_cross_sprite.position());
            _wait_shot_cadence = WAIT_SHOT_CADENCE;
        }
    }
}