#include "arr_timer.h"

namespace arr
{
    Timer::Timer(int frame_time) : 
        _frame_count(frame_time), 
        _frame_interval(frame_time)
    {}

    int Timer::frames_left() {
        return _frame_count;
    }
    
    int Timer::frames_elapsed() {
        return _frame_interval - _frame_count;
    }

    bool Timer::is_time_up()
    {
        _frame_count--;
        if (!_frame_count) {
            _frame_count = _frame_interval;
            return true;
        }
        return false;
    }

    bool Timer::is_time_up_once()
    {
        if (_frame_count > 0) 
        {
            _frame_count--;
            if (!_frame_count) {
                return true;
            }
        }
        return false;
    }

    void Timer::reset_timer() {
        _frame_count = _frame_interval;
    }

    void Timer::reset_timer(int frame_time) {
        _frame_interval = frame_time;
        _frame_count    = frame_time;
    }
}