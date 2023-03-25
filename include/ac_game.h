#ifndef AC_GAME_H
#define AC_GAME_H

// butano
#include "bn_affine_bg_ptr.h"
#include "bn_regular_bg_ptr.h"
// air combat
#include "ac_scene_type.h"
#include "ac_scene.h"
#include "ac_mode_7_camera.h"
#include "ac_player.h"
#include "ac_enemy_spawner.h"
#include "ac_game_events.h"
#include "ac_hud.h"
#include "ac_pause.h"

namespace ac
{
    class Scene;

    class Game : public Scene
    {
        public:
            Game(Game_Events* game_events);
            virtual ~Game() = default;
            virtual bn::optional<Scene_Type> update() final;

        private:
            bn::sprite_ptr _sprite_sheet;
            bn::affine_bg_ptr _mode7_bg;
            bn::regular_bg_ptr _bg;
            Player _player;
            Mode_7_Camera _mode7_cam;
            Enemy_Spawner _enemy_spawner;
            Game_Events* _game_events;
            Hud _hud;
            Pause _pause;
            bn::vector<arr::Circle_Collider*, ac::constants::NUMBER_OF_BULLETS> _bullet_col_vector;
    };
}

#endif