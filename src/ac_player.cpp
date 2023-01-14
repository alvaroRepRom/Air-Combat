#include "ac_player.h"
// butano
#include "bn_math.h"
#include "bn_display.h"
#include "bn_keypad.h"
// air combat
#include "bn_sprite_items_cross.h"

namespace ac
{
    namespace
    {
        constexpr int WAIT_SHOT_CADENCE = 15;
        constexpr int X_BORDER = bn::display::width() / 2 - 20;
        constexpr int Y_BORDER = bn::display::height() / 2 - 20;
        constexpr bn::fixed_point AIM_OFFSET(30, 15);
        constexpr int INIT_Y = 48;
    }

    Player::Player(bn::sprite_ptr& sprite_sheet) : 
        _sprite(sprite_sheet),
        _aim_cross_sprite(bn::sprite_items::cross.create_sprite(0, 0)),
        _player_anim(_sprite),
        _bullet_pool(),
        _wait_shot_cadence(WAIT_SHOT_CADENCE)
    {
        _sprite.set_position(0, INIT_Y);
    }

    void Player::update()
    {       
        _move_aim_cross();
        _move_air_ship();
        _shooting();
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
        else // if not moving to ship X position
        {
            bn::fixed offset_x = X_BORDER - AIM_OFFSET.x();
            if (_aim_cross_sprite.x() > offset_x)
            {
                _aim_cross_sprite.set_x(_aim_cross_sprite.x() - 1);
            }
            else if (_aim_cross_sprite.x() < -offset_x)
            {
                _aim_cross_sprite.set_x(_aim_cross_sprite.x() + 1);
            }
        }
        
        // up and down
        if(bn::keypad::down_held())
        {
            _aim_cross_sprite.set_y(_aim_cross_sprite.y() + 1);
            if (_aim_cross_sprite.y() > Y_BORDER)
                _aim_cross_sprite.set_y(Y_BORDER);
        }
        else if(bn::keypad::up_held())
        {
            _aim_cross_sprite.set_y(_aim_cross_sprite.y() - 1);
            if (_aim_cross_sprite.y() < -Y_BORDER)
                _aim_cross_sprite.set_y(-Y_BORDER);
        }
    }

    void Player::_move_air_ship()
    {
        // MOVE PLAYER X
        bn::fixed x_dist = _aim_cross_sprite.x() - _sprite.x();        
        if (x_dist > 0) // aim to the right
        {
            bn::fixed delta_x = 0.5;
            if (x_dist > AIM_OFFSET.x())
            {
                delta_x = 1;
            }

            if(_sprite.x() < X_BORDER - AIM_OFFSET.x())
                _sprite.set_x(_sprite.x() + delta_x);
        }
        else 
        if (x_dist < 0) // aim to the left
        {
            bn::fixed delta_x = 0.5;
            if (x_dist < -AIM_OFFSET.x())
            {
                delta_x = 1;
            }

            if(_sprite.x() > -X_BORDER + AIM_OFFSET.x())
                _sprite.set_x(_sprite.x() - delta_x);
        }

        // MOVE PLAYER Y
        bn::fixed y_dist = _aim_cross_sprite.y() - _sprite.y() + INIT_Y;
        if (y_dist > 0) // aim down
        {
            bn::fixed delta_y = 0.5;
            if (y_dist > AIM_OFFSET.y())
            {
                delta_y = 1;
            }
            _sprite.set_y(_sprite.y() + delta_y);
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
        }
    }

    void Player::_shooting()
    {
        _bullet_pool.update(); // update active bullets

        _wait_shot_cadence--;
        if (bn::keypad::a_held() && _wait_shot_cadence < 0)
        {
            _bullet_pool.shoot_bullet(_sprite.position());
            _wait_shot_cadence = WAIT_SHOT_CADENCE;
        }
    }
}