#include "ac_test_scene.h"
// butano
#include "bn_sprite_palette_actions.h"
#include "bn_sprite_palettes_actions.h"
// assets
#include "bn_sprite_items_plane_sheet.h"
#include "bn_sprite_palette_items_pink_palette.h"

namespace ac
{
    Test_Scene::Test_Scene() : 
        _sprite(bn::sprite_items::plane_sheet.create_sprite(0, 0)),
        _plane_palette(_sprite.palette())
    {}

    bn::optional<Scene_Type> Test_Scene::update()
    {
        _plane_palette.set_colors(bn::sprite_palette_items::pink_palette);
        bn::optional<Scene_Type> result;
        return result;
    }
}