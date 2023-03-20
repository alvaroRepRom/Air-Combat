#ifndef AC_INTRO_H
#define AC_INTRO_H

// butano
#include "bn_affine_bg_ptr.h"
// air combat
#include "ac_scene_type.h"
#include "ac_scene.h"
// arr
#include "arr_timer.h"

namespace ac
{
    class Scene;

    class Intro : public Scene
    {
        public:
            Intro();
            virtual ~Intro() = default;
            virtual bn::optional<Scene_Type> update() final;

        private:
            bn::affine_bg_ptr _bg;
            arr::Timer _timer;
    };
}

#endif