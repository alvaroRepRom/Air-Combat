#include "ac_title.h"
// butano
#include "bn_keypad.h"
// air combat
#include "ac_scene_type.h"
#include "ac_scene.h"
// assets
#include "bn_regular_bg_items_dungeon_2x.h"

namespace ac
{
    Title::Title() : 
        _bg(bn::regular_bg_items::dungeon_2x.create_bg(0, 0))
    {}

    bn::optional<Scene_Type> Title::update()
    {
        bn::optional<Scene_Type> result;
        
        if (bn::keypad::any_pressed()) result = Scene_Type::GAME;

        return result;
    }
}