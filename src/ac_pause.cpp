#include "ac_pause.h"
// butano
#include "bn_keypad.h"
#include "bn_string.h"
// common
#include "common_variable_8x8_sprite_font.h"

namespace ac
{
    namespace {
        constexpr const bn::string_view PAUSE_LABEL = "PAUSE";
    }

    Pause::Pause() : 
        _is_paused(false),
        _text_generator(common::variable_8x8_sprite_font) 
    {
        _text_generator.set_center_alignment();
    }

    bool Pause::is_game_paused() 
    {
        if (bn::keypad::start_pressed()) 
        {
            _is_paused = !_is_paused;
            _text_sprites.clear();

            if (_is_paused) 
            {
                bn::string<32> text;
        
                bn::ostringstream text_stream(text);
                text_stream.append(PAUSE_LABEL);

                _text_generator.generate(0, 0, text, _text_sprites);
            }
        }
        return _is_paused;
    }
}