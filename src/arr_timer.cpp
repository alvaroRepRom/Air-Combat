#include "arr_timer.h"

namespace arr
{
    Timer::Timer(int frame_time) : 
        _frame_count(frame_time), 
        _frame_interval(frame_time)
    {}

    bool Timer::is_time_up()
    {
        _frame_count--;
        if (!_frame_count) {
            _frame_count = _frame_interval;
            return true;
        }
        return false;
    }
}