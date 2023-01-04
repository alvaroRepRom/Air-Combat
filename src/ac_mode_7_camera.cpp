#include "Intellisense.h"
#include "ac_mode_7_camera.h"
// butano
#include "bn_math.h"
#include "bn_display.h"
#include "bn_keypad.h"
#include "bn_affine_bg_ptr.h"
#include "bn_affine_bg_builder.h"
#include "bn_affine_bg_pa_register_hbe_ptr.h"
#include "bn_affine_bg_pc_register_hbe_ptr.h"
#include "bn_affine_bg_dx_register_hbe_ptr.h"
#include "bn_affine_bg_dy_register_hbe_ptr.h"

namespace
{
    int16_t _pa_values[bn::display::height()];
    int16_t _pc_values[bn::display::height()];
    int _dx_values[bn::display::height()];
    int _dy_values[bn::display::height()];
}

namespace ac 
{
    Mode_7_Camera::Mode_7_Camera(ac::Camera& cam, bn::affine_bg_ptr& bg) 
        : _camera(cam), _bg(bg), 
        _pa_hbe(bn::affine_bg_pa_register_hbe_ptr::create(_bg, _pa_values)),
        _pc_hbe(bn::affine_bg_pc_register_hbe_ptr::create(_bg, _pc_values)),
        _dx_hbe(bn::affine_bg_dx_register_hbe_ptr::create(_bg, _dx_values)),
        _dy_hbe(bn::affine_bg_dy_register_hbe_ptr::create(_bg, _dy_values))
    { }

    void Mode_7_Camera::update()
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

        _update_hbe_values(25);
    }

    int Mode_7_Camera::_speed()
    {
        if(bn::keypad::l_held()) return 40;
        else if(bn::keypad::r_held()) return 22;
        return 32;
    }

    void Mode_7_Camera::_update_hbe_values(int min_index)
    {
        int camera_x = _camera.x.data();
        int camera_y = _camera.y.data() >> 4;
        int camera_z = _camera.z.data();
        int camera_cos = _camera.cos;
        int camera_sin = _camera.sin;
        int y_shift = 160;

        for(int index = min_index; index < bn::display::height(); ++index)
        {
            int reciprocal = bn::reciprocal_lut[index].data() >> 4;
            int lam = camera_y * reciprocal >> 12;
            int lcf = lam * camera_cos >> 8;
            int lsf = lam * camera_sin >> 8;

            _pa_values[index] = int16_t(lcf >> 4);
            _pc_values[index] = int16_t(lsf >> 4);

            int lxr = (bn::display::width() / 2) * lcf;
            int lyr = y_shift * lsf;
            _dx_values[index] = (camera_x - lxr + lyr) >> 4;

            lxr = (bn::display::width() / 2) * lsf;
            lyr = y_shift * lcf;
            _dy_values[index] = (camera_z - lxr - lyr) >> 4;
        }

        _pa_hbe.reload_values_ref();
        _pc_hbe.reload_values_ref();
        _dx_hbe.reload_values_ref();
        _dy_hbe.reload_values_ref();
    }
}