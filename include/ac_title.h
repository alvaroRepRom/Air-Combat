#ifndef AC_TITLE_H
#define AC_TITLE_H

#include "ac_scene_type.h"
#include "ac_scene.h"
#include "bn_regular_bg_ptr.h"

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
            int _frames_to_wait;
    };
}

#endif