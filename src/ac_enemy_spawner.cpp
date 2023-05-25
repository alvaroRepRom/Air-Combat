#include "ac_enemy_spawner.h"
// butano
#include "bn_log.h"
#include "bn_sound_items.h"
// assets
#include "bn_sprite_items_enemy_red.h"
#include "bn_sprite_items_enemy_green.h"
#include "bn_sprite_items_enemy_purple.h"

namespace ac
{
    namespace {
        constexpr const int FRAMES_LEFT_SPAWN_ENEMY = 60;
    }

    Enemy_Spawner::Enemy_Spawner(Game_Events* game_events) : 
        _enemy_array({
            Enemy(bn::sprite_items::enemy_red.create_sprite(0, 0), game_events, Enemy_Type::Type_1),
            Enemy(bn::sprite_items::enemy_green.create_sprite(0, 0), game_events, Enemy_Type::Type_2),
            Enemy(bn::sprite_items::enemy_purple.create_sprite(0, 0), game_events, Enemy_Type::Type_3)
        }),
        _random_generator(),
        _frames_left(FRAMES_LEFT_SPAWN_ENEMY),
        _game_events(game_events)
    {}

    void Enemy_Spawner::update()
    {
        for (int i = 0; i < _enemy_array.size(); i++) 
        {
            if (!_enemy_array.at(i).is_active()) continue;
            _enemy_array.at(i).update();
            
            for (auto bullet_collider : _game_events->bullet_col_f_list)
            {
                if (_enemy_array.at(i).check_collision(*bullet_collider)) {
                    bn::sound_items::explosion.play();
                    _game_events->score += _enemy_array.at(i).score_given();
                }
            }
        }
        
        if (!--_frames_left)
        {
            _frames_left = FRAMES_LEFT_SPAWN_ENEMY;
            if (_random_generator.get_int(5) == 0)
                _spawn();
        }
    }

    void Enemy_Spawner::_spawn()
    {
        for (int i = 0; i < _enemy_array.size(); i++)
        {
            if (!_enemy_array.at(i).is_active())
            {
                _enemy_array.at(i).init();
                return;
            }
        }
    }
}