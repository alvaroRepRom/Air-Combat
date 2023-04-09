#include "ac_game.h"
// butano
#include "bn_affine_bg_builder.h"
#include "bn_keypad.h"
// assets
#include "bn_regular_bg_items_sky.h"
#include "bn_affine_bg_items_ground.h"

namespace ac
{
    Game::Game(Game_Events* game_events) : 
        _mode7_bg(bn::affine_bg_items::ground.create_bg(-376, -336)),
        _bg(bn::regular_bg_items::sky.create_bg(0, 0)),
        _player(game_events),
        _mode7_cam(_mode7_bg),
        _enemy_spawner(game_events),
        _game_events(game_events),
        _hud(),
        _pause()
    {
        _hud.update(0);
    }

    bn::optional<Scene_Type> Game::update()
    {
        bn::optional<Scene_Type> result;

        if (_pause.is_game_paused()) {
            return result;
        }
        
        _player.update();
        _enemy_spawner.update();
        _mode7_cam.update();

        if (_game_events->score) {
            _hud.update(_game_events->score);
            _game_events->score = 0;
        }

        if (bn::keypad::select_pressed()) {
            result = Scene_Type::RANKING;
            _game_events->score = _hud.total_score();
        }

        return result;
    }
}