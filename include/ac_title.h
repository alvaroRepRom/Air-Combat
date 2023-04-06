#ifndef AC_TITLE_H
#define AC_TITLE_H

// butano
#include "bn_sprite_ptr.h"
#include "bn_sprite_palette_ptr.h"
#include "bn_regular_bg_ptr.h"
// air combat
#include "ac_scene_type.h"
#include "ac_scene.h"

namespace ac
{
    class Scene;

    class Title : public Scene
    {
        public:
            Title();
            virtual ~Title() = default;
            virtual bn::optional<Scene_Type> update() final;

        private:
            bn::regular_bg_ptr _bg;
            bn::sprite_ptr _sprite;
            bn::sprite_palette_ptr _sprite_palette;
            int _palette_index;
    };
}

#endif