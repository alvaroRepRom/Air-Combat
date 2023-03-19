#ifndef AC_HUD_H
#define AC_HUD_H

// butano
#include "bn_vector.h"
#include "bn_sprite_text_generator.h"
// air combat
#include "ac_game_events.h"

namespace ac
{
    class Hud
    {
        public:
            Hud();

            void update(int score);
            int total_score();

        private:
            bn::sprite_text_generator _text_generator;
            bn::vector<bn::sprite_ptr, 32> _text_sprites;
            int _total_score;
    };
}

#endif