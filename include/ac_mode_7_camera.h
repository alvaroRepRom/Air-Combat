#ifndef AC_MODE_7_CAMERA_H
#define AC_MODE_7_CAMERA_H

#include "bn_fixed_point.h"
#include "bn_display.h"
#include "bn_affine_bg_ptr.h"
#include "bn_affine_bg_builder.h"
#include "bn_affine_bg_pa_register_hbe_ptr.h"
#include "bn_affine_bg_pc_register_hbe_ptr.h"
#include "bn_affine_bg_dx_register_hbe_ptr.h"
#include "bn_affine_bg_dy_register_hbe_ptr.h"

namespace ac
{
    struct Camera
    {
        bn::fixed x = 440;
        bn::fixed y = 128;
        bn::fixed z = 320;
        int phi = 10;
        int cos = 0;
        int sin = 0;
    };

    class Mode_7_Camera
    {
        private:
            bn::affine_bg_ptr _bg;
            bn::affine_bg_pa_register_hbe_ptr _pa_hbe;
            bn::affine_bg_pc_register_hbe_ptr _pc_hbe;
            bn::affine_bg_dx_register_hbe_ptr _dx_hbe;
            bn::affine_bg_dy_register_hbe_ptr _dy_hbe;
            
            int _speed();

        public:
            Mode_7_Camera(bn::affine_bg_ptr& bg);
            void update_hbe_values(Camera& camera, int min_index);
    };
}

#endif