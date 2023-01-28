#include "ac_bullet.h"
// assets
#include "bn_sprite_items_bullet.h"
#include "bn_log.h"

namespace ac
{
    namespace
    {
        constexpr const int FRAMES_ALIVE = 30; // 0.5 seconds
        constexpr const bn::fixed SCALE_FACTOR = []{
            bn::fixed frames(FRAMES_ALIVE);
            return 1 / frames;
        }();
        bn::fixed h = 8;
    }

    Bullet::Bullet(Game_Events* game_events) : 
        _sprite(bn::sprite_items::bullet.create_sprite(0, 0)),
        col(_sprite, h),
        _game_events(game_events)
    {
        _sprite.set_visible(false);
    }

    void Bullet::init(const bn::fixed_point &shoot_position, const bn::fixed_point &aimed_position)
    {
        _sprite.set_visible(true);
        col.set_sprite(_sprite);

        //_game_events->bullet_col_list.push_front(&col);
        _game_events->bullet_col_list.push_front(col);
        // add a bit more in Y so it's not overlap with ship
        _sprite.set_position(shoot_position.x(), shoot_position.y() - 5);
        _frames_left = FRAMES_ALIVE;
        
        bn::fixed dx = aimed_position.x() - shoot_position.x();
        bn::fixed dy = aimed_position.y() - shoot_position.y();
        _velocity = bn::fixed_point(dx / _frames_left, dy / _frames_left);
    }

    void Bullet::update()
    {
        _sprite.set_position(_sprite.position() + _velocity);

        _frames_left--;
        if (_frames_left)
        {
            _sprite.set_scale(SCALE_FACTOR * _frames_left);
            
        } 
        else 
        {
            _game_events->bullet_col_list.pop_front();
            _sprite.set_visible(false);
        }
    }
    
    bool Bullet::is_active() const
    {
        return _sprite.visible();
    }
}