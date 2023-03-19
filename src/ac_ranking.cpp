#include "ac_ranking.h"
// butano
#include "bn_keypad.h"
#include "bn_string.h"
// air combat
#include "ac_constants.h"
// assets
#include "bn_regular_bg_items_sky.h"
// common
#include "common_variable_8x8_sprite_font.h"

namespace ac
{
    namespace 
    {
        int player_result_position(int score, 
                bn::array<int, ac::constants::NUMBER_SAVES_SCORE> score_array)
        {
            for (int i = 0; i < ac::constants::NUMBER_SAVES_SCORE; i++) {
                if (score > score_array[i])
                    return i;
            }
            return ac::constants::NUMBER_SAVES_SCORE;
        }
    }
    
    Ranking::Ranking(Game_Events* game_events) : 
        _bg(bn::regular_bg_items::sky.create_bg(0, 0)),
        _game_events(game_events),
        _text_generator(common::variable_8x8_sprite_font),
        _current_letter(0),
        _is_start_frame(true),
        _save_data_ranking(Save_Ranking::load_score()),
        _new_record_position(player_result_position(_game_events->score, _save_data_ranking.score_array))
    {
        _text_generator.set_center_alignment();
    }

    bn::optional<Scene_Type> Ranking::update()
    {
        bn::optional<Scene_Type> result;

        if (_is_start_frame) 
        {
            int height = -40;
            int score_index_offset = 0;

            for (int score_index = 0; score_index < ac::constants::NUMBER_SAVES_SCORE; score_index++)
            {
                bn::string<32> text;        
                bn::ostringstream text_stream(text);
                
                for (int i = 0; i < ac::constants::NUMBER_NAME_LETTERS; i++) {
                    text_stream.append(_save_data_ranking.name_array[score_index - score_index_offset][i]);                    
                }

                text_stream.append(":  ");

                if (score_index == _new_record_position) {
                    text_stream.append(_game_events->score);
                    score_index_offset = -1;
                }
                else {
                    text_stream.append(_save_data_ranking.score_array[score_index - score_index_offset]);
                }
                
                _text_generator.generate(0, height, text, _text_sprites_array[score_index]);

                height += 20;
            }

            _is_start_frame = false;
        }
        else
        {
            if (bn::keypad::up_pressed()) {
                _current_letter += 1;
                if (_current_letter > 24)
                    _current_letter = 0;
            }
            else 
            if (bn::keypad::down_pressed()) {
                _current_letter -= 1;
                if (_current_letter < 0)
                    _current_letter = 24;
            }
        }

        return result;
    }

    void Ranking::_save_result()
    {
        Save_Ranking::save_score(_save_data_ranking);
    }
}