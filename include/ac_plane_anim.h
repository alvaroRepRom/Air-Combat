#ifndef AC_PLANE_ANIM_H
#define AC_PLANE_ANIM_H

#include "bn_sprite_ptr.h"
#include "bn_sprite_animate_actions.h"

namespace ac
{
    class Plane_Anim
    {
        private:      
            bn::sprite_ptr _plane;
            bn::sprite_animate_action<4> _action;

        public:
            Plane_Anim(bn::sprite_ptr& sprite);
            void update();
    };
}

#endif