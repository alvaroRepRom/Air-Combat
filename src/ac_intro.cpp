#include "ac_intro.h"
// butano
#include "bn_affine_bg_ptr.h"
#include "bn_affine_bg_builder.h"
// air combat
#include "ac_scene_type.h"
#include "ac_scene.h"
// assets
#include "bn_affine_bg_items_guilty_d_logo.h"

namespace ac
{
    Intro::Intro() : 
        _bg(bn::affine_bg_items::guilty_d_logo.create_bg(0, 0)),
        _frames_to_wait(180) // 3 seconds
    {}

    bn::optional<Scene_Type> Intro::update()
    {
        bn::optional<Scene_Type> result;

        _frames_to_wait--;
        if (_frames_to_wait <= 0) result = Scene_Type::GAME;

        return result;
    }
}