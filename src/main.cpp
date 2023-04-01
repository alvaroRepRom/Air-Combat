//butano
#include "bn_core.h"
#include "bn_music_items.h"
#include "bn_log.h"
// air combat
#include "ac_scene_type.h"
#include "ac_scene.h"
#include "ac_intro.h"
#include "ac_title.h"
#include "ac_game.h"
#include "ac_ranking.h"
#include "ac_game_events.h"
// arr
#include "arr_timer.h"


int main()
{
    bn::core::init();

    bn::optional<ac::Scene_Type> next_scene_type;
    bn::unique_ptr<ac::Scene> scene(new ac::Intro());
    ac::Game_Events game_events;

    bn::music_items::minor_boss_r.play();

// profiling *****
    bn::fixed max_cpu_usage;
    arr::Timer _timer(60);
//*********************

    while(1)
    {
// profiling *******
        if(_timer.is_time_up())
        {
            max_cpu_usage = bn::max(max_cpu_usage, bn::core::last_cpu_usage());
            BN_LOG((max_cpu_usage * 100).right_shift_integer(), "%");
            max_cpu_usage = 0;
        }
//******************
        // Gameloop
        if (scene) next_scene_type = scene->update();
        bn::core::update();
        // Scene Manager
        if (next_scene_type)
        {
            switch (*next_scene_type)
            {
            case ac::Scene_Type::INTRO:
                game_events = ac::Game_Events();
                scene.reset(new ac::Intro());
                break;
            case ac::Scene_Type::TITLE:
                scene.reset(new ac::Title());
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