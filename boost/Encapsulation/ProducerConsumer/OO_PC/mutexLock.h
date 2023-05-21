#ifndef __MUTEXLOCK_H__
#define __MUTEXLOCK_H__

#include <pthread.h>

class MutexLock {
public:
    MutexLock();

    ~MutexLock();

    void lock();

    void tryLock();

    void unlock();

    pthread_mutex_t *getMutexLockPtr();

private:
    pthread_mutex_t _mutex;
};

class MutexLockGuard {
public:
    MutexLockGuard(MutexLock &mutex):_mutex(mutex) {
        _mutex.lock();
    }

    ~MutexLockGuard() {
        _mutex.unlock();
    }
private:
    MutexLock &_mutex;
};



#endif

