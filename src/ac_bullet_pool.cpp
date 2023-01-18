#include "ac_bullet_pool.h"

namespace ac
{
    namespace
    {
        bn::array<Bullet, 1> init_pool()
        {
            bn::array<Bullet, 1> pool;
            for (int i = 0; i < 1; i++)
                pool[i] = Bullet();
            return pool;            
        }
    }

    Bullet_Pool::Bullet_Pool(Game_Events* game_events) : 
        _pool(init_pool()),
        _game_events(game_events)
    {}

    void Bullet_Pool::shoot_bullet(const bn::fixed_point &shoot_position, const bn::fixed_point &aimed_position)
    {
        for(int i = 0; i < _pool.size(); i++)
        {
            if (!_pool[i].is_active())
            {
                _pool[i].init(shoot_position, aimed_position);
                _game_events->bullet_collider = &_pool[i].collider;
                return;
            }
        }
    }

    void Bullet_Pool::update()
    {
        for(int i = 0; i < _pool.size(); i++)
            if (_pool[i].is_active()) 
                _pool[i].update();
    }
}