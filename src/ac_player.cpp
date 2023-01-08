#include "ac_player.h"
// butano
#include "bn_math.h"
#include "bn_display.h"
#include "bn_keypad.h"
// air combat

namespace ac
{
    Player::Player(Camera& camera, bn::sprite_ptr sprite_sheet) : 
        camera(camera), 
        _sprite(sprite_sheet),
        _player_anim(_sprite)
    {}

    void Player::update()
    {
        // turn left and right
        bn::fixed dir_x = 0;

        if(bn::keypad::left_held())
        {
            dir_x -= bn::fixed::from_data(32); // to left
            //gira izquierda
            camera.phi -= 4;            
            if(camera.phi < 0) // límite del angulo
                camera.phi += 2048;
        }
        else if(bn::keypad::right_held())
        {
            dir_x += bn::fixed::from_data(32); // to right
            // giro derecha
            camera.phi += 4;
            if(camera.phi >= 2048) // angle limit
                camera.phi -= 2048;
        }

        // up and down
        if(bn::keypad::down_held())
        {
            camera.y += bn::fixed::from_data(2048); // up
        }
        else if(bn::keypad::up_held())
        {
            camera.y -= bn::fixed::from_data(2048); // down
            if(camera.y < 0) // if lower than ground
                camera.y = 0;
        }

        // Fly speed
        bn::fixed dir_z = -bn::fixed::from_data(_speed()); // forward

        // Magic Actual Movement
        camera.cos = bn::lut_cos(camera.phi).data() >> 4;
        camera.sin = bn::lut_sin(camera.phi).data() >> 4;
        camera.x += (dir_x * camera.cos) - (dir_z * camera.sin);
        camera.z += (dir_x * camera.sin) + (dir_z * camera.cos);

        // Animations
        _player_anim.update();
    }

    int Player::_speed()
    {
        if(bn::keypad::l_held()) return 40;
        else if(bn::keypad::r_held()) return 22;
        return 32;
    }
}