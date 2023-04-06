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
        _bg(bn::regular_bg_items::dungeon_2x.create_bg(0, 0)),
        _sprite(),
        _sprite_palette(_sprite.palette()),
        _palette_index(0)
    {}

    bn::optional<Scene_Type> Title::update()
    {
        bn::optional<Scene_Type> result;

        if (bn::keypad::left_pressed()) {
            _palette_index--
            if (_palette_index < 0)
                _palette_index = 1;
        } 
        else 
        if (bn::keypad::right_pressed()) {
            _palette_index++
            if (_palette_index > 1)
                _palette_index = 0;
        }
        
        if (bn::keypad::a_pressed()) {
            result = Scene_Type::GAME;
        }

        return result;
    }
}