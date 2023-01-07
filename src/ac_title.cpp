#include "ac_title.h"
// butano
// air combat
#include "ac_scene_type.h"
#include "ac_scene.h"
// assets
#include "bn_regular_bg_items_dungeon_2x.h"

namespace ac
{
    namespace
    {
        constexpr int num_frames = 180;
    }

    Title::Title() : 
        _bg(bn::regular_bg_items::dungeon_2x.create_bg(0, 0)),
        _frames_to_wait(num_frames) // 3 seconds
    {}

    bn::optional<Scene_Type> Title::update()
    {
        bn::optional<Scene_Type> result;
        
        _frames_to_wait--;
        if (!_frames_to_wait) result = Scene_Type::GAME;

        return result;
    }
}