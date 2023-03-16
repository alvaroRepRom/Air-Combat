#include "ac_hud.h"
// butano
#include "bn_display.h"
#include "bn_string.h"
// common
#include "common_variable_8x8_sprite_font.h"

namespace ac
{
    namespace
    {
        //bn::window outside_window = bn::window::outside();
        constexpr bn::fixed text_x_limit = bn::display::width() / 2 - 10;
        constexpr bn::fixed text_y_limit = -bn::display::height() / 2 + 7;
        constexpr bn::string_view score_label = "SCORE: ";
    }

    Hud::Hud(Game_Events* game_events) : 
        _game_events(game_events),
        _text_generator(common::variable_8x8_sprite_font)
    {
        _text_generator.set_right_alignment();
    }


    void Hud::update(int score)
    {
        bn::string<32> text;

        bn::ostringstream text_stream(text);
        text_stream.append(score_label);
        text_stream.append(score);

        _text_sprites.clear();
        _text_generator.generate(text_x_limit, text_y_limit, text, _text_sprites);
    }
}