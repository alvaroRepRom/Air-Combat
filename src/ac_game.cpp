#include "ac_game.h"
// butano
#include "bn_core.h"
#include "bn_keypad.h"
#include "bn_affine_bg_ptr.h"
#include "bn_affine_bg_builder.h"
// air combat
#include "ac_mode_7_camera.h"
#include "ac_player.h"
#include "ac_scene_type.h"
#include "ac_scene.h"
// assets
#include "bn_sprite_items_plane_sheet.h"
#include "bn_affine_bg_items_ground.h"
#include "bn_regular_bg_items_sky.h"

namespace ac
{
    namespace
    {
        Camera create_camera()
        {
            Camera cam;
            return cam;
        }
    }

    Game::Game() : 
        _cam(create_camera()), 
        _sprite_sheet(bn::sprite_items::plane_sheet.create_sprite(0, -48)),
        _mode7_bg(bn::affine_bg_items::ground.create_bg(-376, -336)),
        _player(_cam, _sprite_sheet),
        _mode7_cam(_mode7_bg),
        _bg(bn::regular_bg_items::sky.create_bg(0, 0))
    {}

    bn::optional<Scene_Type> Game::update()
    {
        bn::optional<Scene_Type> result;

        _player.update();
        _mode7_cam.update_hbe_values(_player.camera, 25);

        return result;
    }
}