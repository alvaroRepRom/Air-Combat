#ifndef AC_CONTROLLER_H
#define AC_CONTROLLER_H

#include "ac_mode_7_camera.h"

namespace ac
{
    class Controller
    {
        private:      
            ac::Camera _camera;            
            int _speed();

        public:
            Controller(ac::Camera& cam);
            void update();
    };

    bool is_paused();
}

#endif