#ifndef AC_TITLE_H
#define AC_TITLE_H

// butano
#include "bn_sprite_ptr.h"
#include "bn_regular_bg_ptr.h"
// air combat
#include "ac_scene_type.h"
#include "ac_scene.h"
#include "ac_game_events.h"
// arr
#include "arr_timer.h"

namespace ac
{
    class Scene;

    class Title : public Scene
    {
        public:
            Title(Game_Events* game_events);
            virtual ~Title() = default;
            virtual bn::optional<Scene_Type> update() final;

        private:
            bn::regular_bg_ptr _bg;
            bn::sprite_ptr _sprite;
            bn::sprite_ptr _arrow_select;
            bool _is_right_arrow;
            int _palette_index;
            Game_Events* _game_events;
            arr::Timer _arrow_timer;
    };
}

#endif