//butano
#include "bn_core.h"
#include "bn_music_items.h"
// air combat
#include "ac_scene_type.h"
#include "ac_scene.h"
#include "ac_intro.h"
#include "ac_title.h"
#include "ac_game.h"
#include "ac_ranking.h"
#include "ac_game_events.h"
#include "ac_test_scene.h"

int main()
{
    bn::core::init();

    bn::optional<ac::Scene_Type> next_scene_type;
    bn::unique_ptr<ac::Scene> scene(new ac::Intro());
    ac::Game_Events game_events;

    bn::music_items::air_combat.play();

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
                game_events = ac::Game_Events();
                scene.reset(new ac::Title(&game_events));
                break;
            case ac::Scene_Type::GAME:
                scene.reset(new ac::Game(&game_events));
                break;
            case ac::Scene_Type::RANKING:
                scene.reset(new ac::Ranking(game_events.score));
                break;
            default:
                BN_ERROR("Invalid next scene: ", int(*next_scene_type));
                break;
            }
        }        
    }
}