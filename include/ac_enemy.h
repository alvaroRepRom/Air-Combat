#ifndef AC_ENEMY_H
#define AC_ENEMY_H

// butano
#include "bn_sprite_ptr.h"
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

            virtual ~Enemy() = default;
            
            void init();
            void update();
            bool is_active();
            void deactivate();

            void on_collision() override;

        private:
            bn::sprite_ptr _sprite;
            int _frames_left;
            bool _goes_up;
            bool _goes_right;
            Game_Events* _game_events;
    };
}

#endif