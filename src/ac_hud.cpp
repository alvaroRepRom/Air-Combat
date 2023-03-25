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
        constexpr const bn::fixed TEXT_X_LIMIT = bn::display::width() / 2 - 10;
        constexpr const bn::fixed TEXT_Y_LIMIT = -bn::display::height() / 2 + 7;
        constexpr const bn::string_view SCORE_LABEL = "SCORE: ";
    }

    Hud::Hud() : 
        _text_generator(common::variable_8x8_sprite_font),
        _total_score(0)
    {
        _text_generator.set_right_alignment();
    }


    void Hud::update(int score)
    {
        _total_score += score;
        
        bn::string<32> text;
        
        bn::ostringstream text_stream(text);
        text_stream.append(SCORE_LABEL);
        text_stream.append(_total_score);

        _text_sprites.clear();
        _text_generator.generate(TEXT_X_LIMIT, TEXT_Y_LIMIT, text, _text_sprites);
    }
    
    int Hud::total_score() { 
        return _total_score; 
    }
}