#ifndef AC_GAME_H
#define AC_GAME_H

// butano
#include "bn_affine_bg_ptr.h"
#include "bn_regular_bg_ptr.h"
#include "bn_pool.h"
// air combat
#include "ac_scene_type.h"
#include "ac_scene.h"
#include "ac_mode_7_camera.h"
#include "ac_plane_anim.h"
#include "ac_player.h"
#include "ac_enemy_spawner.h"

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
            bn::sprite_ptr _sprite_sheet;
            bn::affine_bg_ptr _mode7_bg;
            bn::regular_bg_ptr _bg;
            Player _player;
            Mode_7_Camera _mode7_cam;
            Enemy_Spawner _enemy_spawner;
    };
}

#endif