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
        for (auto enemy : _enemy_pool)
        {
            if (enemy.is_active())
            {
                enemy.update();

                if (_game_events->bullet_col_list.empty()) continue;
                
                for (auto bullet_col : _game_events->bullet_col_list)
                {
                    if (arr::check_collision(bullet_col, enemy.col))
                    {
                        enemy.deactivate();
                        BN_LOG("has Collide?: ", true);
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