#include "ac_title.h"
// butano
#include "bn_keypad.h"
#include "bn_array.h"
#include "bn_sprite_palette_ptr.h"
// assets
#include "bn_regular_bg_items_sky.h"
#include "bn_sprite_items_plane_sheet.h"
#include "bn_sprite_palette_items_pink_palette.h"
#include "bn_sprite_palette_items_red_palette.h"

namespace ac
{
    namespace {
        constexpr const bn::array<const bn::sprite_palette_item, 3> palette_array{
            bn::sprite_items::plane_sheet.palette_item(),
            bn::sprite_palette_items::pink_palette,
            bn::sprite_palette_items::red_palette
        };
    }

    Title::Title(Game_Events* game_events) : 
        _bg(bn::regular_bg_items::sky.create_bg(0, 0)),
        _sprite(bn::sprite_items::plane_sheet.create_sprite(0, 0)),
        _palette_index(0),
        _game_events(game_events)
    {}

    bn::optional<Scene_Type> Title::update()
    {
        bn::optional<Scene_Type> result;

        if (bn::keypad::left_pressed()) {
            _palette_index--;
            if (_palette_index < 0)
                _palette_index = palette_array.size() - 1;

            _sprite.set_palette(palette_array[_palette_index]);
        } 
        else 
        if (bn::keypad::right_pressed()) {
            _palette_index++;
            if (_palette_index >= palette_array.size())
                _palette_index = 0;

            _sprite.set_palette(palette_array[_palette_index]);
        }
        
        if (bn::keypad::start_pressed()) {
            _game_events->ship_palette = 
                bn::sprite_palette_ptr::create_optional(palette_array[_palette_index]);
            
            result = Scene_Type::GAME;
        }
        else
        if (bn::keypad::b_pressed()) {
            result = Scene_Type::RANKING;
        }

        return result;
    }
}