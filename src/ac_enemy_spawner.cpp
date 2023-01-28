#include "ac_enemy_spawner.h"
#include "bn_log.h"
#include "arr_collisions.h"

namespace ac
{
    namespace
    {
        bn::array<Enemy, constants::NUMBER_OF_ENEMIES> init_pool()
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
        _enemy_pool(init_pool()),
        _game_events(game_events)
    {}

    void Enemy_Spawner::update()
    {
        for (int i = 0; i < _enemy_pool.size(); i++)
        {
            if (_enemy_pool[i].is_active())
            {
                _enemy_pool[i].update();

                if (!_game_events->bullet_col_list.empty())
                {
                    for (int index = 0; index < _game_events->bullet_col_list.size(); index++)
                    {
                        if (arr::check_collision(_game_events->bullet_col_list[index], _enemy_pool[i].col))
                        {
                            _enemy_pool[i].deactivate();
                            //_game_events->bullet_col_list.pop_front();
                            BN_LOG("has Collide?: ", true);
                        }
                        else
                        {
                            //_game_events->bullet_col_list.end();
                        }
                    }
                }
            }
        }
        
        _frames_left--;
        if (!_frames_left)
        {
            _frames_left = 60;
            if (_random_generator.get_int(5) == 0)
                spawn();
        }
    }

    void Enemy_Spawner::spawn()
    {
        for (int i = 0; i < _enemy_pool.size(); i++)
        {
            if (!_enemy_pool[i].is_active())
            {
                _enemy_pool[i].init();
                return;
            }
        }
    }
}