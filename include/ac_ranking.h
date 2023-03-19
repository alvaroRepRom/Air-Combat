#ifndef AC_RANKING_H
#define AC_RANKING_H

// butano
#include "bn_regular_bg_ptr.h"
#include "bn_vector.h"
#include "bn_array.h"
#include "bn_sprite_text_generator.h"
// air combat
#include "ac_scene_type.h"
#include "ac_scene.h"
#include "ac_game_events.h"
#include "ac_save_ranking.h"

namespace ac
{
    class Scene;

    class Ranking : public Scene
    {
        public:
            Ranking(Game_Events* game_events);
            virtual ~Ranking() = default;
            virtual bn::optional<Scene_Type> update() final;

        private:
            bn::regular_bg_ptr _bg;
            Game_Events* _game_events;
            bn::sprite_text_generator _text_generator;
            bn::array<bn::vector<bn::sprite_ptr, 32>, ac::constants::NUMBER_SAVES_SCORE> _text_sprites_array;
            int _current_letter;
            bool _is_start_frame;
            Save_Ranking::SRam_Data _save_data_ranking;
            int _new_record_position;

            void _save_result();
    };
}

#endif