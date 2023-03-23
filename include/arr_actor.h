#ifndef ARR_ACTOR_H
#define ARR_ACTOR_H

// arr
#include "arr_circle_collider.h"

namespace arr
{
    class Actor
    {
        public:
            virtual ~Actor() = default;
            virtual void update() = 0;
        protected:
            Actor() = default;
    };
}

#endif