#include "arr_timer.h"

namespace arr
{
    Timer::Timer(unsigned int frame_time) : 
        _frame_timer(frame_time), 
        _frame_interval(frame_time)
    {}

    int Timer::frames_left() {
        return _frame_timer;
    }
    
    int Timer::frames_elapsed() {
        return _frame_interval - _frame_timer;
    }

    bool Timer::is_time_up()
    {
        if (!--_frame_timer) {
            _frame_timer = _frame_interval;
            return true;
        }
        return false;
    }

    bool Timer::is_time_up_once()
    {
        if (!_frame_timer) 
            return false;
        return !--_frame_timer;
    }

    void Timer::reset_timer() {
        _frame_timer = _frame_interval;
    }

    void Timer::reset_timer(unsigned int frame_time) {
        _frame_interval = frame_time;
        _frame_timer    = frame_time;
    }
}