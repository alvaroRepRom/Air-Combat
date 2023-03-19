#ifndef AC_BULLET_H
#define AC_BULLET_H

// butano
#include "bn_sprite_ptr.h"
#include "bn_fixed_point.h"
// air combat
#include "ac_game_events.h"
// arr
#include "arr_circle_collider.h"

namespace ac
{
    class Game_Events;

    class Bullet : public arr::Circle_Collider
    {
        public:
            Bullet();
            Bullet(bn::sprite_ptr sprite, Game_Events* game_events);

            void update();
            void init(const bn::fixed_point &shoot_position, const bn::fixed_point &aimed_position);
            bool is_active();

            void on_collision() override;

        private:
            bn::sprite_ptr _sprite;
            bn::fixed_point _velocity;
            int _frames_left;
            bool _is_active;
            bool _is_first_frame;
            Game_Events* _game_events;

            void _deactivate();
    };
}

#endif