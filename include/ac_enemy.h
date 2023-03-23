#ifndef AC_ENEMY_H
#define AC_ENEMY_H

// butano
#include "bn_sprite_ptr.h"
#include "bn_fixed_point.h"
// air combat
#include "ac_game_events.h"
// arr
#include "arr_circle_collider.h"

namespace ac
{
    class Enemy : public arr::Circle_Collider
    {
        public:
            Enemy(bn::sprite_ptr sprite, Game_Events* game_events);
            //arr::Circle_Collider col;

            virtual ~Enemy() = default;
            
            void init();
            void update();
            bool is_active();
            void deactivate();

            void on_collision() override;

        private:
            bn::sprite_ptr _sprite;
            bn::fixed_point _velocity;
            int _frames_left;
            bn::fixed _dx;
            bn::fixed _dy;
            bool _goes_up;
            bool _goes_right;
            Game_Events* _game_events;
    };
}

#endif