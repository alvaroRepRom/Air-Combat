#include "ac_intro.h"
// butano
#include "bn_core.h"
#include "bn_affine_bg_ptr.h"
#include "bn_affine_bg_builder.h"
// air combat
#include "ac_scene_type.h"
#include "ac_scene.h"
// assets
#include "bn_affine_bg_items_guilty_d_logo.h"

namespace ac
{
    Intro::Intro() : _bg(bn::affine_bg_items::guilty_d_logo.create_bg(0, 0))
    {}

    bn::optional<Scene_Type> Intro::update()
    {
        for(int index = 0; index < 180; ++index) // wait 3 seconds
            bn::core::update();

        return Scene_Type::GAME;
    }
}