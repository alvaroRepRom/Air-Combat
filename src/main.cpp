//butano
#include "bn_core.h"
//#include "bn_math.h"
//#include "bn_cameras.h"
//#include "bn_display.h"
//#include "bn_camera_ptr.h"
//#include "bn_affine_bg_ptr.h"
//#include "bn_affine_bg_builder.h"
//#include "bn_bg_palettes.h"
//#include "bn_sprite_ptr.h"
//#include "bn_regular_bg_builder.h"
//#include "bn_regular_bg_attributes.h"
//#include "bn_regular_bg_position_hbe_ptr.h"
//#include "bn_regular_bg_attributes_hbe_ptr.h"
#include "bn_assert.h"
// air combat
//#include "ac_mode_7_camera.h"
//#include "ac_controller.h"
//#include "ac_plane_anim.h"
#include "ac_scene_type.h"
#include "ac_scene.h"
#include "ac_intro.h"
#include "ac_game.h"
// assets
//#include "bn_affine_bg_items_ground.h"
//#include "bn_regular_bg_items_sky.h"
//#include "bn_sprite_items_plane_sheet.h"
//#include "bn_sound_items.h"

int main()
{
    bn::core::init();
    
    //ac::Camera cam;
    //bn::affine_bg_ptr bg = bn::affine_bg_items::ground.create_bg(-376, -336);
    
    //ac::Controller controller(ac::Controller{cam});
    //ac::Mode_7_Camera mode_7_cam(ac::Mode_7_Camera(cam, bg));

    //bn::regular_bg_ptr sky = bn::regular_bg_items::sky.create_bg(0, 0);
    
    //bn::sprite_ptr player = bn::sprite_items::plane_sheet.create_sprite(0, 0);
    //ac::Plane_Anim plane_anim(player);

    bn::optional<ac::Scene_Type> next_scene_type(ac::Scene_Type::INTRO);
    bn::unique_ptr<ac::Scene> scene;;
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

        if (wait_frame_transition > 0) continue;

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

                /*
                // shoot
                if (bn::keypad::a_pressed())
                {
                    bn::sound_items::gun_2.play();
                }
                //controller.update();
                //mode_7_cam.update();
                plane_anim.update();
                if (ac::is_paused()) 
                {
                    bn::core::reset();
                }
                */
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