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

            sram_data.score_array[0] = 100;
            sram_data.score_array[1] = 80;
            sram_data.score_array[2] = 60;
            sram_data.score_array[3] = 40;
            sram_data.score_array[4] = 20;

            for (int i = 0; i < ac::constants::NUMBER_SAVES_SCORE; i++)
            {
                sram_data.first_letter_array[0] = 'A';
                sram_data.second_letter_array[0] = 'A';
                sram_data.third_letter_array[0] = 'A';
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