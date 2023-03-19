#ifndef AC_SAVE_RANKING_H
#define AC_SAVE_RANKING_H

// butano
#include "bn_array.h"
// air combat
#include "ac_constants.h"

namespace ac::Save_Ranking
{
    struct SRam_Data
    {
        bool is_default = true;
        bn::array<int, ac::constants::NUMBER_SAVES_SCORE> score_array;
        bn::array<bn::array<char, ac::constants::NUMBER_NAME_LETTERS>, 
                            ac::constants::NUMBER_SAVES_SCORE> name_array;
    };
    
    void save_score(SRam_Data sram_data);
    
    SRam_Data load_score();
    
    void reset_score();
}

#endif