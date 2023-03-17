//butano
#include "bn_core.h"
#include "bn_log.h"
// air combat
#include "ac_scene_type.h"
#include "ac_scene.h"
#include "ac_intro.h"
#include "ac_title.h"
#include "ac_game.h"

#include "ac_save_ranking.h"

int main()
{
    bn::core::init();

    bn::optional<ac::Scene_Type> next_scene_type;
    bn::unique_ptr<ac::Scene> scene(new ac::Intro());



// save system *********
    // ac::Save_Ranking::SRam_Data sram_data;
    // sram_data.max_score = 30;
    // ac::Save_Ranking::save_score(sram_data);

    //ac::Save_Ranking::reset_score();
    ac::Save_Ranking::SRam_Data loaded_data = ac::Save_Ranking::load_score();

    for (int i = 0; i < ac::constants::NUMBER_SAVES_SCORE; i++)
    {
        BN_LOG(i + 1, ":  => ", loaded_data.score_array[i]);
        //BN_LOG(i + 1, ": ", loaded_data.name_score_array[i] , " => ", loaded_data.score_array[i]);
    }
// ***************


// profiling *****
    bn::fixed max_cpu_usage;
    int counter = 60;
//*********************

    while(1)
    {
// profiling *******
        counter--;
        if(! counter)
        {
            max_cpu_usage = bn::max(max_cpu_usage, bn::core::last_cpu_usage());
            BN_LOG((max_cpu_usage * 100).right_shift_integer(), "%");
            max_cpu_usage = 0;
            counter = 60;
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