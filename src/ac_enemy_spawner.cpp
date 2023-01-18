#include "ac_enemy_spawner.h"
#include "bn_log.h"

namespace ac
{
    Enemy_Spawner::Enemy_Spawner(Game_Events* game_events) : 
        _frames_left(60),
        _random_generator(),
        _enemy_pool({Enemy(), Enemy(), Enemy()}),
        _game_events(game_events)
    {}

    void Enemy_Spawner::update()
    {
        for (int i = 0; i < _enemy_pool.size(); i++){
            _enemy_pool[i].update();
            bool collide = _enemy_pool[i].collider.check_collision(*_game_events->bullet_collider);
            if (collide) BN_LOG("has Collide?: ", collide);
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