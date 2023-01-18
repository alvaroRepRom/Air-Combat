#include "ac_intro.h"
// butano
#include "bn_affine_bg_builder.h"
// air combat
#include "ac_constants.h"
// assets
#include "bn_affine_bg_items_guilty_d_logo.h"
#include "bn_affine_bg_items_butano_background.h"

namespace ac
{
    namespace
    {
        constexpr int NUM_FRAMES = constants::FPS * 3; // 3 seconds
    }

    Intro::Intro() : 
        _bg(bn::affine_bg_items::guilty_d_logo.create_bg(0, 0)),
        _frames_to_wait(NUM_FRAMES)
    {}

    bn::optional<Scene_Type> Intro::update()
    {
        bn::optional<Scene_Type> result;
        
        _frames_to_wait--;
        if (_frames_to_wait == NUM_FRAMES / 2) _bg = bn::affine_bg_items::butano_background.create_bg(0, 0);
        if (!_frames_to_wait) result = Scene_Type::TITLE;

        return result;
    }
}