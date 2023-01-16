#include "ac_enemy_spawner.h"
// butano

namespace ac
{
    Enemy_Spawner::Enemy_Spawner() : 
        _frames_left(60),
        _random_generator(),
        _enemy_pool({Enemy(), Enemy(), Enemy()})
    {}

    void Enemy_Spawner::update()
    {
        for (int i = 0; i < _enemy_pool.size(); i++)
            _enemy_pool[i].update();
        
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