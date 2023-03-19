#include "ac_save_ranking.h"
// butano
#include "bn_sram.h"

namespace ac::Save_Ranking
{
    namespace
    {
        constexpr SRam_Data init_save_score_data()
        {
            SRam_Data sram_data;

            sram_data.is_default = false;
            int default_score = 100;

            for (int i = 0; i < ac::constants::NUMBER_SAVES_SCORE; i++) {
                sram_data.score_array[i] = default_score;
                default_score -= 20;
                for (int j = 0; j < ac::constants::NUMBER_NAME_LETTERS; j++)
                    sram_data.name_array[i][j] = 'A';
            }
            
            return sram_data;
        }
    }

    /**
     * @brief Saves the max scores of the game
     */
    void save_score(SRam_Data sram_data)
    {
        sram_data.is_default = false;
        bn::sram::write(sram_data);
    }

    /**
     * @brief Load the max scores of the game
     */
    SRam_Data load_score()
    {
        SRam_Data cart_sram_data;
        bn::sram::read(cart_sram_data);

        if (cart_sram_data.is_default)
            cart_sram_data = init_save_score_data();

        return cart_sram_data;
    }

    /**
     * @brief Reset the max scores of the game
     */
    void reset_score()
    {
        bn::sram::clear(bn::sram::size());
    }
}