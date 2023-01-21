#ifndef AC_MODE_7_CAMERA_H
#define AC_MODE_7_CAMERA_H

#include "bn_affine_bg_ptr.h"
#include "bn_affine_bg_pa_register_hbe_ptr.h"
#include "bn_affine_bg_pc_register_hbe_ptr.h"
#include "bn_affine_bg_dx_register_hbe_ptr.h"
#include "bn_affine_bg_dy_register_hbe_ptr.h"

namespace ac
{
    class Mode_7_Camera
    {
        private:
            bn::affine_bg_pa_register_hbe_ptr _pa_hbe;
            bn::affine_bg_pc_register_hbe_ptr _pc_hbe;
            bn::affine_bg_dx_register_hbe_ptr _dx_hbe;
            bn::affine_bg_dy_register_hbe_ptr _dy_hbe;

        public:
            Mode_7_Camera(bn::affine_bg_ptr& bg);
            void update();
    };
}

#endif