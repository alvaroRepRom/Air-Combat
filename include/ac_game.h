#ifndef AC_GAME_H
#define AC_GAME_H

// butano
#include "ac_scene_type.h"
#include "ac_scene.h"
#include "bn_affine_bg_ptr.h"
// air combat
#include "ac_mode_7_camera.h"
#include "ac_controller.h"
#include "ac_plane_anim.h"

namespace ac
{
    class Scene;

    class Game : public Scene
    {
        public:
            Game();
            virtual ~Game() = default;
            virtual bn::optional<Scene_Type> update() final;

        private:
            Camera _cam;
            bn::affine_bg_ptr _bg;
    };
}

#endif