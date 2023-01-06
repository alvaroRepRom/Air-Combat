//butano
#include "bn_core.h"
#include "bn_assert.h"
#include "bn_affine_bg_ptr.h"
// air combat
#include "ac_scene_type.h"
#include "ac_scene.h"
#include "ac_intro.h"
#include "ac_game.h"
// assets
#include "bn_affine_bg_items_cuad.h"

int main()
{
    bn::core::init();

    bn::optional<ac::Scene_Type> next_scene_type(ac::Scene_Type::INTRO);
    bn::unique_ptr<ac::Scene> scene(new ac::Intro());
    int wait_frame_transition = 30;
    
    while(true)
    {
        // Gameloop
        if (scene) next_scene_type = scene -> update();

        bn::core::update();

        // Scene Manager
        if (!next_scene_type) continue;

        if (scene)
        {
            wait_frame_transition = 30;
            scene.reset();
        }
        wait_frame_transition--;

        if (wait_frame_transition) continue;

        switch (*next_scene_type)
        {
            case ac::Scene_Type::INTRO:
                scene.reset(new ac::Intro());
                break;
            case ac::Scene_Type::TITLE:
                next_scene_type = ac::Scene_Type::GAME;
                break;
            case ac::Scene_Type::GAME:
                scene.reset(new ac::Game());
                break;
            default:
                BN_ERROR("Invalid scene_type ", "in main.cpp");
                break;
        }
    }
}

/*
// Control tipo micromachines
int main()
{
    bn::core::init();
    bn::affine_bg_ptr cuad = bn::affine_bg_items::cuad.create_bg(0, 0);
    bn::sprite_ptr player = bn::sprite_items::pivot.create_sprite(0, 0);
    bn::camera_ptr camera = bn::camera_ptr::create(0, 0);

    cuad.set_camera(camera);
    cuad.set_wrapping_enabled(false);

    player.set_camera(camera);

    while(true)
    {
        bn::fixed rotation_angle = player.rotation_angle();
    
        if(bn::keypad::left_held())
            player.set_rotation_angle(rotation_angle < 1 ? 360 : rotation_angle - 1);
        else 
        if(bn::keypad::right_held())
            player.set_rotation_angle(rotation_angle > 359 ? 0 : rotation_angle + 1);


        if(bn::keypad::l_held()){
            bn::fixed dx = bn::degrees_sin(rotation_angle);
            bn::fixed dy = bn::degrees_cos(rotation_angle);
            player.set_position(player.x() + dx, player.y() - dy);
        }
        else 
        if(bn::keypad::r_held()){
            bn::fixed dx = bn::degrees_sin(rotation_angle);
            bn::fixed dy = bn::degrees_cos(rotation_angle);
            player.set_position(player.x() + dx, player.y() + dy);
        }

        camera.set_position(player.position());

        bn::core::update();
    }
}
*/