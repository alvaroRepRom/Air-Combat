#ifndef ARR_EVENT_H
#define ARR_EVENT_H

// butano
#include "bn_sprite_ptr.h"
#include "bn_fixed_point.h"
#include "bn_array.h"
#include "bn_deque.h"
// air combat
#include "ac_constants.h"
// arr
#include "arr_box_collider.h"
#include "arr_circle_collider.h"
#include "arr_collisions.h"

namespace arr
{
    class Event
    {
        public:
            virtual ~Event() = default;
            virtual void action() = 0;
        protected:
            Event() = default;
    };
}

#endif