#ifndef ARR_TIMER_H
#define ARR_TIMER_H

namespace arr
{
    class Timer
    {
        public:
            Timer(unsigned int frame_time);

            int frames_left();
            int frames_elapsed();

            bool is_time_up();
            bool is_time_up_once();
            void reset_timer();
            void reset_timer(unsigned int frame_time);

        private:
            unsigned int _frame_timer;
            unsigned int _frame_interval;
    };
}

#endif