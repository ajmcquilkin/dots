#pragma once

#include "mutex.hpp"

class ScopedLock
{
    public:
        ScopedLock(Mutex &mutex);
        ~ScopedLock();
    
    private:
        Mutex &_mutex;
};
