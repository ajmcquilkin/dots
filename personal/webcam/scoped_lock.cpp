#include "scoped_lock.hpp"

ScopedLock::ScopedLock(Mutex & mutex)
    : _mutex(mutex)
{
    _mutex.lock();
}

ScopedLock::~ScopedLock()
{
    _mutex.unlock();
}
