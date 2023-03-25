#include "ac_ranking.h"
// butano
#include "bn_keypad.h"
#include "bn_string.h"
#include "bn_log.h"
// air combat
#include "ac_scene_type.h"
#include "ac_constants.h"
// assets
#include "bn_regular_bg_items_sky.h"
// common
#include "common_variable_8x8_sprite_font.h"

namespace ac
{
    namespace 
    {
        constexpr int player_result_position(int score, 
                bn::array<int, constants::NUMBER_SAVES_SCORE> score_array)
        {
            for (int i = 0; i < constants::NUMBER_SAVES_SCORE; i++) {
                if (score > score_array.at(i))
                    return i;
            }
            return constants::NUMBER_SAVES_SCORE;
        }

        constexpr const int A_LETTER = 65;
        constexpr const int Z_LETTER = 90;
    }
    
    Ranking::Ranking(int player_score) : 
        _bg(bn::regular_bg_items::sky.create_bg(0, 0)),
        _text_generator(common::variable_8x8_sprite_font),
        _current_letter_index(0),
        _save_data_ranking(Save_Ranking::load_score()),
        _new_record_position(player_result_position(player_score, _save_data_ranking.score_array)),
        _player_score(player_score)
    {
        _text_generator.set_center_alignment();

        for (int j = 0; j < _name_inserted.size(); j++)
            _name_inserted.at(j) = A_LETTER;
    }

    bn::optional<Scene_Type> Ranking::update()
    {
        bn::optional<Scene_Type> result;

        if (bn::keypad::up_pressed()) {
            _name_inserted.at(_current_letter_index) += 1;
            if (_name_inserted.at(_current_letter_index) > Z_LETTER)
                _name_inserted.at(_current_letter_index) = A_LETTER;
        }
        else 
        if (bn::keypad::down_pressed()) {
            _name_inserted.at(_current_letter_index) -= 1;
            if (_name_inserted.at(_current_letter_index) < A_LETTER)
                _name_inserted.at(_current_letter_index) = Z_LETTER;
        }
        else
        if (bn::keypad::left_pressed()) {
            _current_letter_index -= 1;
            if (_current_letter_index < 0)
                _current_letter_index = constants::NUMBER_NAME_LETTERS - 1;
        }
        else 
        if (bn::keypad::right_pressed()) {
            _current_letter_index += 1;
            if (_current_letter_index > constants::NUMBER_NAME_LETTERS - 1)
                _current_letter_index = 0;
        }


        int height = -40;
        int score_index_offset = 0;

        for (int rank_pos = 0; rank_pos < constants::NUMBER_SAVES_SCORE; rank_pos++)
        {
            bn::string<32> text;        
            bn::ostringstream text_stream(text);

            if (rank_pos == _new_record_position) {
                // insert name
                for (int j = 0; j < _name_inserted.size(); j++) {
                    text_stream.append(char(_name_inserted[j]));
                }                
                text_stream.append(":  ");
                text_stream.append(_player_score);
                score_index_offset = 1;                
            }
            else {
                for (int i = 0; i < ac::constants::NUMBER_NAME_LETTERS; i++) {
                    text_stream.append(_save_data_ranking.name_array[rank_pos - score_index_offset][i]);                    
                }
                text_stream.append(":  ");
                text_stream.append(_save_data_ranking.score_array[rank_pos - score_index_offset]);
            }

            _text_sprites_array[rank_pos].clear();
            _text_generator.generate(0, height, text, _text_sprites_array[rank_pos]);
            height += 20;
        }

        if (bn::keypad::start_pressed()) {
            result = Scene_Type::INTRO;
            if (_new_record_position != constants::NUMBER_SAVES_SCORE)
                _save_result();
        }

        return result;
    }

    void Ranking::_save_result()
    {
        for (int rank_pos = constants::NUMBER_SAVES_SCORE - 1; rank_pos >= 0; rank_pos--)
        {
            if (rank_pos == _new_record_position) {
                // Add New Record
                _save_data_ranking.score_array[rank_pos] = _player_score;
                for (int i = 0; i < constants::NUMBER_NAME_LETTERS; i++) {
                    _save_data_ranking.name_array[rank_pos][i] = (char)_name_inserted[i];
                }
                break;
            }
            else {
                // Move Rank Down
                _save_data_ranking.score_array[rank_pos] = _save_data_ranking.score_array[rank_pos - 1];
                for (int i = 0; i < constants::NUMBER_NAME_LETTERS; i++) {
                    _save_data_ranking.name_array[rank_pos][i] = _save_data_ranking.name_array[rank_pos - 1][i];
                }
            }
        }

        Save_Ranking::save_score(_save_data_ranking);
    }
}