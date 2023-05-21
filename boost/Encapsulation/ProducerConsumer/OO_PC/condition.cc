#include "condition.h"
#include <stdio.h>

#include "mutexLock.h"


Condition::Condition(MutexLock &mutex):_mutex(mutex) {
       int ret = pthread_cond_init(&_cond, nullptr);
       if(ret) {
           perror("pthread_cond_init");
           return;
       }
}

Condition::~Condition() {
       int ret = pthread_cond_destroy(&_cond);
       if(ret) {
           perror("pthread_cond_destroy");
           return;
       }
}

void Condition::wait() {
    //这里要得一把锁，通过引用数据成员找到，
    //但是MutexLock中的锁是私有的，需要提供一个接口得到锁
       int ret = pthread_cond_wait(&_cond, _mutex.getMutexLockPtr());
       if(ret) {
           perror("pthread_cond_destroy");
           return;
       }
}

void Condition::notify() {
       int ret = pthread_cond_signal(&_cond);
       if(ret) {
           perror("pthread_cond_signal");
           return;
       }
}

void Condition::notifyAll() {
       int ret = pthread_cond_broadcast(&_cond);
       if(ret) {
           perror("pthread_cond_broadcast");
           return;
       }
}
