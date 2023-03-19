#ifndef ARR_TIMER_H
#define ARR_TIMER_H

// butano
#include "bn_fixed.h"

namespace arr
{
    class Timer
    {
        public:
            Timer(int frame_time);

            bool is_time_up();
            bool is_time_up_once();
            void reset_timer();
            void reset_timer(int frame_time);

        private:
            int _frame_count;
            int _frame_interval;
    };
}

#endif