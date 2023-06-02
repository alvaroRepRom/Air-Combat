#ifndef AC_EVENT_H
#define AC_EVENT_H

#include "bn_deque.h"

namespace arr
{
    class EventArgs { }

    template<typename TArg0>
    class Event
    {
    private:
        typedef void(*FuncPtr)(TArg0);        
        typedef bn::deque<FuncPtr, 8> FuncPtrSeq;

        FuncPtrSeq ls;

    public:
        Event& operator += (FuncPtr func)
        {
            ls.push_back(func);
            return *this;
        }

        void operator()(TArg0 x) 
        { 
            for (typename FuncPtrSeq::iterator it(ls.begin()); it != ls.end(); ++it)
                (*it)(x);
        }
    };
}
#endif