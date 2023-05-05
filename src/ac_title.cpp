#include "ac_title.h"
// butano
#include "bn_keypad.h"
#include "bn_array.h"
#include "bn_sprite_palette_ptr.h"
// assets
#include "bn_regular_bg_items_title.h"
#include "bn_sprite_items_arrow.h"
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
        _bg(bn::regular_bg_items::title.create_bg(0, 0)),
        _sprite(bn::sprite_items::plane_sheet.create_sprite(0, 16)),
        _arrow_select(bn::sprite_items::arrow.create_sprite(72, 16)),
        _is_right_arrow(true),
        _palette_index(0),
        _game_events(game_events),
        _arrow_timer(30)
    {
        _arrow_select.set_visible(false);
    }

    bn::optional<Scene_Type> Title::update()
    {
        bn::optional<Scene_Type> result;

        if (_arrow_select.visible()) {
            if (_arrow_timer.is_time_up()) {
                _arrow_select.set_visible(false);
            }
        }

        if (bn::keypad::left_pressed()) {
            _palette_index--;
            if (_palette_index < 0)
                _palette_index = palette_array.size() - 1;

            _sprite.set_palette(palette_array[_palette_index]);

            _arrow_select.set_visible(true);
            _arrow_select.set_x(-72);
            _arrow_select.set_horizontal_flip(true);
        } 
        else 
        if (bn::keypad::right_pressed()) {
            _palette_index++;
            if (_palette_index >= palette_array.size())
                _palette_index = 0;

            _sprite.set_palette(palette_array[_palette_index]);

            _arrow_select.set_visible(true);
            _arrow_select.set_x(72);
            _arrow_select.set_horizontal_flip(false);
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