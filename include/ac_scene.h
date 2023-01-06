#ifndef AC_SCENE_H
#define AC_SCENE_H

#include "bn_optional_fwd.h"
#include "ac_scene_type.h"

namespace ac
{
    enum class Scene_Type;

    class Scene
    {
        public:
            virtual ~Scene() = default;
            [[nodiscard]] virtual bn::optional<Scene_Type> update() = 0;
        protected:
            Scene() = default;
    };
}

#endif