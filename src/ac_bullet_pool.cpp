#include "ac_bullet_pool.h"
// assets
#include "bn_sprite_items_bullet.h"
#include "bn_log.h"

namespace ac
{
    namespace
    {/*
        bn::array<Bullet, constants::NUMBER_OF_BULLETS> init_pool(Game_Events* game_events)
        {
            bn::array<Bullet, constants::NUMBER_OF_BULLETS> pool;
            for (int i = 0; i < pool.size(); i++)
                pool[i] = Bullet(bn::sprite_items::bullet.create_sprite(0, 0), game_events);
            return pool;
        }*/
    }

    Bullet_Pool::Bullet_Pool(Game_Events* game_events) : 
        _game_events(game_events),
        _pool({Bullet(bn::sprite_items::bullet.create_sprite(0, 0), game_events), 
            Bullet(bn::sprite_items::bullet.create_sprite(0, 0), game_events), 
            Bullet(bn::sprite_items::bullet.create_sprite(0, 0), game_events)})
        //_pool(init_pool(_game_events))
    {}

    void Bullet_Pool::shoot_bullet(const bn::fixed_point &shoot_position, const bn::fixed_point &aimed_position)
    {
        for(int i = 0; i < _pool.size(); i++)
        {
            if (!_pool[i].is_active())
            {
                _pool[i].init(shoot_position, aimed_position);
                //_game_events->bullet_col_list.push_front(&_pool[i].col);
                return;
            }
        }
    }

    void Bullet_Pool::update()
    {
        BN_LOG("inside");
        if (_pool.empty()) return;
        BN_LOG("not empty");
        for(int i = 0; i < _pool.size(); i++)
            if (_pool[i].is_active()) 
                _pool[i].update();
    }
}