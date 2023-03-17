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

            // sram_data.name_score_array[0] = "AAA";
            // sram_data.name_score_array[1] = "BBB";
            // sram_data.name_score_array[2] = "CCC";
            // sram_data.name_score_array[3] = "DDD";
            // sram_data.name_score_array[4] = "EEE";

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