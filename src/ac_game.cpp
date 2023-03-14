#include "ac_game.h"
// butano
#include "bn_affine_bg_builder.h"
// air combat
// assets
#include "bn_sprite_items_plane_sheet.h"
#include "bn_regular_bg_items_sky.h"
#include "bn_affine_bg_items_fondo.h"
#include "bn_affine_bg_items_ground.h"

namespace ac
{
    Game::Game() : 
        _sprite_sheet(bn::sprite_items::plane_sheet.create_sprite(0, 0)),
        _mode7_bg(bn::affine_bg_items::ground.create_bg(-376, -336)),
        _player(_sprite_sheet, _game_events),
        _mode7_cam(_mode7_bg),
        _bg(bn::regular_bg_items::sky.create_bg(0, 0)),
        _enemy_spawner(_game_events)
    {}

    bn::optional<Scene_Type> Game::update()
    {
        bn::optional<Scene_Type> result;

        _player.update();        
        _enemy_spawner.update();
        _mode7_cam.update();
        
        return result;
    }
}