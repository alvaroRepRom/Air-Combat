#include "ac_game.h"
// butano
#include "bn_affine_bg_builder.h"
// air combat
// assets
#include "bn_sprite_items_plane_sheet.h"
#include "bn_affine_bg_items_ground.h"
#include "bn_regular_bg_items_sky.h"
#include "bn_affine_bg_items_fondo.h"

namespace ac
{
    Game::Game() : 
        _sprite_sheet(bn::sprite_items::plane_sheet.create_sprite(0, -48)),
        _mode7_bg(bn::affine_bg_items::fondo.create_bg(-376, -336)),
        _player(_sprite_sheet),
        _mode7_cam(_mode7_bg),
        _bg(bn::regular_bg_items::sky.create_bg(0, 0))
    {}

    bn::optional<Scene_Type> Game::update()
    {
        bn::optional<Scene_Type> result;

        _player.update();
        _mode7_cam.update_hbe_values(_player.camera, 25);

        return result;
    }
}