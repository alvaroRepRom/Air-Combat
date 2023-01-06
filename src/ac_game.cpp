#include "ac_game.h"
// butano
#include "bn_core.h"
#include "bn_keypad.h"
#include "bn_affine_bg_ptr.h"
#include "bn_affine_bg_builder.h"
// air combat
#include "ac_mode_7_camera.h"
#include "ac_controller.h"
#include "ac_plane_anim.h"
#include "ac_scene_type.h"
#include "ac_scene.h"
// assets
#include "bn_sprite_items_plane_sheet.h"
#include "bn_affine_bg_items_ground.h"

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

    Game::Game() : _cam(create_camera()), _bg(bn::affine_bg_items::ground.create_bg(-376, -336))
    {}

    bn::optional<Scene_Type> Game::update()
    {
        bn::sprite_ptr player = bn::sprite_items::plane_sheet.create_sprite(0, 0);
        Plane_Anim _plane_anim(player);
        if (bn::keypad::a_pressed())
        {
            bn::sound_items::gun_2.play();
        }
        //controller.update();
        //mode_7_cam.update();
        _plane_anim.update();
        if (ac::is_paused()) 
        {
            bn::core::reset();
        }
    }
}