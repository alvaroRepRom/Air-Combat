#include "ac_bullet.h"
// butano
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
        constexpr const bn::fixed h = 8;
        constexpr const int y_shoot_offset = 5;
    }

    Bullet::Bullet(bn::sprite_ptr sprite, Game_Events &game_events) : 
        arr::Circle_Collider(sprite, h),
        _game_events(game_events),
        _sprite(sprite),
        col(_sprite, h)
    {
        _sprite.set_visible(false);
        set_enabled(false);
        _frames_left = FRAMES_ALIVE;
        _is_active = false;
    }

    void Bullet::init(const bn::fixed_point &shoot_position, const bn::fixed_point &aimed_position)
    {
        _sprite.set_visible(true);
        set_enabled(true);
        _is_active = true;
        //col.set_sprite(_sprite);

        _game_events.bullet_col_f_list.push_front(this);
        
        // add a bit more in Y so it's not overlap with ship
        _sprite.set_position(shoot_position.x(), shoot_position.y() - y_shoot_offset);
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
            BN_LOG(SCALE_FACTOR * _frames_left);
            _sprite.set_scale(SCALE_FACTOR * _frames_left);
        } 
        else 
        {
            _sprite.set_visible(false);
            set_enabled(false);
            _is_active = false;
            _game_events.bullet_col_f_list.remove(this);
        }
    }
    
    bool Bullet::is_active()
    {
        return _is_active;//_sprite.visible();
    }

    void Bullet::on_collision() // override from circle_collision
    {
        _is_active = false;
        _sprite.set_visible(false);
        set_enabled(false);
        _game_events.bullet_col_f_list.remove(this);
    }
}