#include "ac_bullet_pool.h"
// butano

namespace ac
{
    namespace
    {
        bn::array<Bullet, 10> init_pool()
        {
            bn::array<Bullet, 10> pool;
            for (int i = 0; i < 10; i++)
                pool[i] = Bullet();
            return pool;            
        }
    }

    Bullet_Pool::Bullet_Pool() : _pool(init_pool())
    {}

    void Bullet_Pool::shoot_bullet(bn::fixed_point shoot_position)
    {
        for(int i = 0; i < _pool.size(); i++)
        {
            if (!_pool[i].is_active())
            {
                _pool[i].init(shoot_position);
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