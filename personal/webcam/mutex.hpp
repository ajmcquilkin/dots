#pragma once

#include <mutex>

class Mutex
{
    public:
        Mutex();
        ~Mutex();

        void lock();
        void unlock();

    private:
        pthread_mutex_t m_mutex;
};