#ifndef AC_TEST_SCENE_H
#define AC_TEST_SCENE_H

// butano
#include "bn_sprite_ptr.h"
#include "bn_sprite_palette_ptr.h"
// air combat
#include "ac_scene_type.h"
#include "ac_scene.h"

namespace ac
{
    class Scene;

    class Test_Scene : public Scene
    {
        public:
            Test_Scene();
            virtual ~Test_Scene() = default;
            virtual bn::optional<Scene_Type> update() final;

            bn::optional<const bn::sprite_palette_ptr> ship_palette;

        private:
            bn::sprite_ptr _sprite;
            bn::sprite_palette_ptr _plane_palette;

    };
}
#endif