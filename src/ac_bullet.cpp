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

    Bullet::Bullet(bn::sprite_ptr sprite, Game_Events* game_events) : 
        arr::Circle_Collider(sprite, h),
        _game_events(game_events),
        _sprite(sprite),
        _frames_left(FRAMES_ALIVE),
        _is_first_frame(true)
    {
        _deactivate();
    }

    void Bullet::init(const bn::fixed_point &shoot_position, const bn::fixed_point &aimed_position)
    {
        _sprite.set_visible(true);
        set_collision_enabled(true);
        _is_active = true;
        set_radius(h);

        if (_is_first_frame) {
            _game_events->bullet_col_f_list.push_front(this);
            _is_first_frame = false;
        }
        
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
        if (_frames_left) {
            _sprite.set_scale(SCALE_FACTOR * _frames_left);
            set_radius(h * SCALE_FACTOR * _frames_left);
        } 
        else {
            _deactivate();
        }
    }
    
    bool Bullet::is_active() 
    {
        return _is_active;
    }

    void Bullet::on_collision() // override from circle_collision
    {
        _deactivate();
    }

    void Bullet::_deactivate()
    {
        _is_active = false;
        _sprite.set_visible(false);
        set_collision_enabled(false);
    }
}