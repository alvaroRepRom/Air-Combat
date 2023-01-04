#include "Intellisense.h"
#include "ac_controller.h"
//butano
#include "bn_math.h"
#include "bn_keypad.h"

namespace ac
{
    Controller::Controller(ac::Camera& cam) : _camera(cam)
    { }

    void Controller::update()
    {
        bn::fixed dir_x = 0;

        // turn
        if(bn::keypad::left_held())
        {
            dir_x -= bn::fixed::from_data(32); // a izquiera
            //gira izquierda
            _camera.phi -= 4;            
            if(_camera.phi < 0) // límite del angulo
                _camera.phi += 2048;
        }
        else if(bn::keypad::right_held())
        {
            dir_x += bn::fixed::from_data(32); // a derecha
            // giro derecha
            _camera.phi += 4;
            if(_camera.phi >= 2048) // límite del angulo
                _camera.phi -= 2048;
        }

        // up and down
        if(bn::keypad::down_held())
        {
            _camera.y += bn::fixed::from_data(2048); // arriba
        }
        else if(bn::keypad::up_held())
        {
            // abajo
            _camera.y -= bn::fixed::from_data(2048);
            if(_camera.y < 0) // si llega al suelo
                _camera.y = 0;
        }

        // Fly speed
        bn::fixed dir_z = -bn::fixed::from_data(_speed()); // adelante

        // Magic Actual Movement
        _camera.cos = bn::lut_cos(_camera.phi).data() >> 4;
        _camera.sin = bn::lut_sin(_camera.phi).data() >> 4;
        _camera.x += (dir_x * _camera.cos) - (dir_z * _camera.sin);
        _camera.z += (dir_x * _camera.sin) + (dir_z * _camera.cos);
    }

    int Controller::_speed()
    {
        if(bn::keypad::l_held()) return 40;
        else if(bn::keypad::r_held()) return 22;
        return 32;
    }

    bool is_paused(){
        return bn::keypad::start_pressed();
    }
}