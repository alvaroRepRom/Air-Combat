#include "ac_bullet_pool.h"
// butano

namespace ac
{
    namespace
    {
        bn::array<Bullet, 3> init_pool()
        {
            bn::array<Bullet, 3> pool;
            for (int i = 0; i < 3; i++)
                pool[i] = Bullet();
            return pool;            
        }
    }

    Bullet_Pool::Bullet_Pool() : _pool(init_pool())
    {}

    void Bullet_Pool::shoot_bullet(bn::fixed_point shoot_position, bn::fixed_point aimed_position)
    {
        for(int i = 0; i < _pool.size(); i++)
        {
            if (!_pool[i].is_active())
            {
                _pool[i].init(shoot_position, aimed_position);
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