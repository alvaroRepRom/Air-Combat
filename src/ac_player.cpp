#include "ac_player.h"
// butano
#include "bn_keypad.h"

namespace ac
{
    Player::Player(ac::Camera& cam, bn::sprite_ptr sprite_sheet) : 
        _camera(cam), 
        _sprite(sprite_sheet)
    {}

    void Player::update()
    {
        // turn left and right
        bn::fixed dir_x = 0;

        if(bn::keypad::left_held())
        {
            dir_x -= bn::fixed::from_data(32); // to left
            //gira izquierda
            _camera.phi -= 4;            
            if(_camera.phi < 0) // límite del angulo
                _camera.phi += 2048;
        }
        else if(bn::keypad::right_held())
        {
            dir_x += bn::fixed::from_data(32); // to right
            // giro derecha
            _camera.phi += 4;
            if(_camera.phi >= 2048) // angle limit
                _camera.phi -= 2048;
        }

        // up and down
        if(bn::keypad::down_held())
        {
            _camera.y += bn::fixed::from_data(2048); // up
        }
        else if(bn::keypad::up_held())
        {
            // down
            _camera.y -= bn::fixed::from_data(2048);
            if(_camera.y < 0) // if lower than ground
                _camera.y = 0;
        }

        // Fly speed
        bn::fixed dir_z = -bn::fixed::from_data(_speed()); // forward

        // Magic Actual Movement
        _camera.cos = bn::lut_cos(_camera.phi).data() >> 4;
        _camera.sin = bn::lut_sin(_camera.phi).data() >> 4;
        _camera.x += (dir_x * _camera.cos) - (dir_z * _camera.sin);
        _camera.z += (dir_x * _camera.sin) + (dir_z * _camera.cos);
    }

    int Player::_speed()
    {
        if(bn::keypad::l_held()) return 40;
        else if(bn::keypad::r_held()) return 22;
        return 32;
    }
}