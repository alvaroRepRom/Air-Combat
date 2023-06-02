#include "ac_player.h"
// butano
#include "bn_math.h"
#include "bn_display.h"
#include "bn_keypad.h"
#include "bn_sound_items.h"
// assets
#include "bn_sprite_items_cross.h"
#include "bn_sprite_items_plane_sheet.h"
#include "bn_sprite_items_bullet.h"

namespace ac
{
    namespace
    {
        constexpr const int WAIT_SHOT_CADENCE = 15;
        constexpr const int X_BORDER = bn::display::width() / 2 - 20;
        constexpr const int Y_BORDER = bn::display::height() / 2 - 20;
        constexpr const bn::fixed_point AIM_OFFSET(30, 15);
        constexpr const int INIT_Y = 48;
        constexpr const bn::fixed SOUND_VOLUME(0.2);
    }

    Player::Player(Game_Events* game_events) : 
        _sprite(bn::sprite_items::plane_sheet.create_sprite(0, 0)),
        _aim_cross_sprite(bn::sprite_items::cross.create_sprite(0, 0)),
        _wait_shot_cadence(WAIT_SHOT_CADENCE),
        _bullet_array({ 
            Bullet(bn::sprite_items::bullet.create_sprite(0, 0), game_events), 
            Bullet(bn::sprite_items::bullet.create_sprite(0, 0), game_events), 
            Bullet(bn::sprite_items::bullet.create_sprite(0, 0), game_events)
        }),
        _sprite_palette(*game_events->ship_palette.get())
    {
        _sprite.set_position(0, INIT_Y);
        _sprite.set_palette(_sprite_palette);
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

        // MOVE SHIP Y
        bn::fixed y_dist = _aim_cross_sprite.y() - _sprite.y() + INIT_Y;
        if (y_dist > 0) // aim down
        {
            bn::fixed delta_y = 0.5;
            sprite_index = 3;
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
            sprite_index = 2;
            if (y_dist < -AIM_OFFSET.y())
            {
                delta_y = 1;
            }
            _sprite.set_y(_sprite.y() - delta_y);

            // STOP UP ship movement 
            if (_sprite.y() < -Y_BORDER + INIT_Y + AIM_OFFSET.y())
                _sprite.set_y(-Y_BORDER + INIT_Y + AIM_OFFSET.y());
        }

        
        // MOVE SHIP X
        bn::fixed x_dist = _aim_cross_sprite.x() - _sprite.x();        
        if (x_dist > 0) // IF aim to the right
        {
            sprite_index = 1;
            bn::fixed delta_x = 0.5;
            if (x_dist > AIM_OFFSET.x())
            {
                //sprite_index = 2;
                delta_x = 1;
            }

            if (_sprite.x() < X_BORDER - AIM_OFFSET.x())
                _sprite.set_x(_sprite.x() + delta_x);
        }
        else 
        if (x_dist < 0) // IF aim to the left
        {
            sprite_index = 4;
            bn::fixed delta_x = 0.5;
            if (x_dist < -AIM_OFFSET.x())
            {
                //sprite_index = 6;
                delta_x = 1;
            }

            if(_sprite.x() > -X_BORDER + AIM_OFFSET.x())
                _sprite.set_x(_sprite.x() - delta_x);
        }        

        _sprite.set_item(bn::sprite_items::plane_sheet, sprite_index);
        _sprite.set_palette(_sprite_palette);
    }

    void Player::_shooting()
    {
        _wait_shot_cadence--;        
        for (int i = 0; i < _bullet_array.size(); i++)
        {
            if (_bullet_array[i].is_active()) {
                _bullet_array[i].update();
            }
            else 
            if (bn::keypad::a_held() && _wait_shot_cadence < 0)
            {
                _bullet_array[i].init(_sprite.position(), _aim_cross_sprite.position());
                bn::sound_items::shoot.play(SOUND_VOLUME);               
                _wait_shot_cadence = WAIT_SHOT_CADENCE;
            }
        }
    }
}