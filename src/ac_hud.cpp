#include "ac_hud.h"
// butano
#include "bn_vector.h"
// common
#include "common_variable_8x8_sprite_font.h"

namespace ac
{
    namespace
    {
        //bn::window outside_window = bn::window::outside();
    }

    Hud::Hud(Game_Events* game_events) : 
        _game_events(game_events),
        _text_generator(common::variable_8x8_sprite_font)
    {
        
    }


    void Hud::update()
    {
        bn::vector<bn::sprite_ptr, 32> text_sprites;
        _text_generator.generate(0, -5, "Text", text_sprites);
    }
}