#include "ac_title.h"
// butano
#include "bn_keypad.h"
#include "bn_array.h"
// air combat
#include "ac_scene_type.h"
#include "ac_scene.h"
// assets
#include "bn_regular_bg_items_dungeon_2x.h"
#include "bn_sprite_items_plane_sheet.h"
#include "bn_sprite_palette_items_pink_palette.h"

namespace ac
{
    namespace {
        constexpr const bn::array<const bn::sprite_palette_item, 2> palette_array{
            bn::sprite_items::plane_sheet.palette_item(),
            bn::sprite_palette_items::pink_palette
        };
    }

    Title::Title() : 
        _bg(bn::regular_bg_items::dungeon_2x.create_bg(0, 0)),
        _sprite(bn::sprite_items::plane_sheet.create_sprite(0, 0)),
        _sprite_palette(_sprite.palette()),
        _palette_index(0)
    {}

    bn::optional<Scene_Type> Title::update()
    {
        bn::optional<Scene_Type> result;

        if (bn::keypad::left_pressed()) {
            _palette_index--;
            if (_palette_index < 0)
                _palette_index = palette_array.size() - 1;

            _sprite_palette.set_colors(palette_array[_palette_index]);
        } 
        else 
        if (bn::keypad::right_pressed()) {
            _palette_index++;
            if (_palette_index >= palette_array.size())
                _palette_index = 0;

            _sprite_palette.set_colors(palette_array[_palette_index]);
        }
        
        if (bn::keypad::a_pressed()) {
            result = Scene_Type::GAME;
        }
        else
        if (bn::keypad::b_pressed()) {
            result = Scene_Type::RANKING;
        }

        return result;
    }
}