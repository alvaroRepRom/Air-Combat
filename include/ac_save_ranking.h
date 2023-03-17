#ifndef AC_SAVE_RANKING_H
#define AC_SAVE_RANKING_H

// butano
#include "bn_array.h"
#include "bn_string.h"
// air combat
#include "ac_constants.h"

namespace ac::Save_Ranking
{
    struct SRam_Data
    {
        bool is_default = true;
        bn::array<int, ac::constants::NUMBER_SAVES_SCORE> score_array;
        //bn::array<bn::string<32>, ac::constants::NUMBER_SAVES_SCORE> name_score_array;
    };
    
    void save_score(SRam_Data sram_data);
    
    SRam_Data load_score();
    
    void reset_score();
}

#endif