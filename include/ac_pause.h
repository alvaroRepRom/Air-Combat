#ifndef AC_PAUSE_H
#define AC_PAUSE_H

// butano
#include "bn_vector.h"
#include "bn_sprite_text_generator.h"
#include "bn_sprite_ptr.h"

namespace ac
{
    class Pause
    {
        public:
            Pause();

            bool is_game_paused();

        private:
            bool _is_paused;
            bn::sprite_text_generator _text_generator;
            bn::vector<bn::sprite_ptr, 32> _text_sprites;
    };
}

#endif