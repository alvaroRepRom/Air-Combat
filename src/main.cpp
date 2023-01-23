//butano
#include "bn_core.h"
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
        bn::core::update();
        // Scene Manager
        if (next_scene_type)
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
}