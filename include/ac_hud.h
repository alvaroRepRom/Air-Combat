#ifndef AC_HUD_H
#define AC_HUD_H

// butano
#include "bn_affine_bg_ptr.h"
#include "bn_regular_bg_ptr.h"
#include "bn_sprite_text_generator.h"
// air combat
#include "ac_game_events.h"

namespace ac
{
    class Hud
    {
        public:
            Hud(Game_Events* game_events);

            void update();

        private:
            Game_Events* _game_events;
            bn::sprite_text_generator _text_generator;
            
    };
}

#endif