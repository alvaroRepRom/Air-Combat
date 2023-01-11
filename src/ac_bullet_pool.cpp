#include "ac_bullet_pool.h"
// butano
#include "bn_keypad.h"

namespace ac
{
    Bullet_Pool::Bullet_Pool() : _pool({
        Bullet(), Bullet(),Bullet(),Bullet(),Bullet(),
        Bullet(),Bullet(),Bullet(),Bullet(),Bullet()
    })
    {}

    void Bullet_Pool::shoot_bullet(bn::fixed_point shoot_position)
    {
        for(int i = 0; i < _pool.size(); i++)
        {
            if (!_pool[i].is_been_used())
            {
                _pool[i].init(shoot_position);
                return;
            }
        }
    }

    void Bullet_Pool::update()
    {
        for(int i = 0; i < _pool.size(); i++)
            if (_pool[i].is_been_used())
                _pool[i].update();
    }
}