#ifndef __MUTEXLOCK_H__
#define __MUTEXLOCK_H__

#include <pthread.h>

class MutexLock {
public:
   MutexLock();
   ~MutexLock();

   void lock();
   void trylock();
   void unlock();

   //在cond_wait函数参数中需要一把锁
   pthread_mutex_t *getMutex();

private:
    pthread_mutex_t _mutex;
};

//RAII思想，利用栈对象析构解锁
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

