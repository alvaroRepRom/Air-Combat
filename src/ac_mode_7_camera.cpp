#include "ac_mode_7_camera.h"
// butano
#include "bn_math.h"
#include "bn_display.h"
#include "bn_affine_bg_builder.h"

namespace
{
    int16_t _pa_values[bn::display::height()];
    int16_t _pc_values[bn::display::height()];
    int _dx_values[bn::display::height()];
    int _dy_values[bn::display::height()];
    constexpr bn::fixed Z_SPEED = -bn::fixed::from_data(40); // forward
    const int MIN_INDEX = 25;
}

namespace ac 
{
    Mode_7_Camera::Mode_7_Camera(bn::affine_bg_ptr& bg) : 
        _bg(bg),
        _pa_hbe(bn::affine_bg_pa_register_hbe_ptr::create(_bg, _pa_values)),
        _pc_hbe(bn::affine_bg_pc_register_hbe_ptr::create(_bg, _pc_values)),
        _dx_hbe(bn::affine_bg_dx_register_hbe_ptr::create(_bg, _dx_values)),
        _dy_hbe(bn::affine_bg_dy_register_hbe_ptr::create(_bg, _dy_values))
    {
        _camera.cos = bn::lut_cos(_camera.phi).data() >> 4;
        _camera.sin = bn::lut_sin(_camera.phi).data() >> 4;
    }

    void Mode_7_Camera::update()
    {
        // Magic Actual Movement
        _camera.z += Z_SPEED * _camera.cos;
        _update_hbe_values();
    }

    void Mode_7_Camera::_update_hbe_values()
    {
        int camera_x = _camera.x.data();
        int camera_y = _camera.y.data() >> 4;
        int camera_z = _camera.z.data();
        int camera_cos = _camera.cos;
        int camera_sin = _camera.sin;
        int y_shift = 160;

        for(int index = MIN_INDEX; index < bn::display::height(); ++index)
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