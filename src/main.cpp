//butano
#include "bn_core.h"
#include "bn_assert.h"
#include "bn_affine_bg_ptr.h"
// air combat
#include "ac_scene_type.h"
#include "ac_scene.h"
#include "ac_intro.h"
#include "ac_title.h"
#include "ac_game.h"

int main()
{
    bn::core::init();

    bn::optional<ac::Scene_Type> next_scene_type;
    bn::unique_ptr<ac::Scene> scene(new ac::Intro());
    
    while(1)
    {
        // Gameloop
        if (scene) next_scene_type = scene->update();
        // Scene Manager
        if (next_scene_type)
        {
            if (scene)
                scene.reset();
            else
            {
                switch (*next_scene_type)
                {
                case ac::Scene_Type::INTRO:
                    scene.reset(new ac::Intro());
                    break;
                case ac::Scene_Type::TITLE:
                    scene.reset(new ac::Title());
                    break;
                case ac::Scene_Type::GAME:
                    scene.reset(new ac::Game());
                    break;
                default:
                    BN_ERROR("Invalid next scene: ", int(*next_scene_type));
                    break;
                }
            }
        }
        bn::core::update();
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