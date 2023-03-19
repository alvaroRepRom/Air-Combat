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
            Ranking(int player_score);
            virtual ~Ranking() = default;
            virtual bn::optional<Scene_Type> update() final;

        private:
            bn::regular_bg_ptr _bg;
            Game_Events* _game_events;
            bn::sprite_text_generator _text_generator;
            bn::array<bn::vector<bn::sprite_ptr, 32>, ac::constants::NUMBER_SAVES_SCORE> _text_sprites_array;
            bn::array<int, ac::constants::NUMBER_NAME_LETTERS> _name_inserted;
            int _current_letter_index;
            Save_Ranking::SRam_Data _save_data_ranking;
            int _new_record_position;
            int _player_score;

            void _save_result();
    };
}

#endif