// butano
#include "bn_array.h"
// air combat
#include "ac_enemy_spawner.h"
#include "bn_log.h"
// arr
#include "arr_collisions.h"

namespace ac
{
    namespace
    {
        bn::array<Enemy, constants::NUMBER_OF_ENEMIES> init_enemy_array()
        {
            bn::array<Enemy, constants::NUMBER_OF_ENEMIES> pool;
            for (int i = 0; i < pool.size(); i++)
                pool[i] = Enemy();
            return pool;
        }
    }

    Enemy_Spawner::Enemy_Spawner(Game_Events* game_events) : 
        _frames_left(60),
        _random_generator(),
        _enemy_array(init_enemy_array()),
        _game_events(game_events)
    {}

    void Enemy_Spawner::update()
    {        
        for (int i = 0; i < _enemy_array.size(); i++)
        {
            if (!_enemy_array[i].is_active()) continue;

            _enemy_array[i].update();
            
            for (auto bullet_collider : _game_events->bullet_col_f_list)
            {
                if (bullet_collider->is_collision_enabled())
                {
                    if (arr::check_collision(*bullet_collider, _enemy_array[i].col))
                    {
                        _enemy_array[i].deactivate();
                        bullet_collider->on_collision();
                    }
                }
            }
        }
        
        _frames_left--;
        if (!_frames_left)
        {
            _frames_left = 60;
            if (_random_generator.get_int(5) == 0)
                _spawn();
        }
    }

    void Enemy_Spawner::_spawn()
    {
        for (int i = 0; i < _enemy_array.size(); i++)
        {
            if (!_enemy_array[i].is_active())
            {
                _enemy_array[i].init();
                return;
            }
        }
    }
}