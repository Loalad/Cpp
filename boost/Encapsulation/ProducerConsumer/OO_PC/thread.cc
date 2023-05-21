#include "thread.h"
#include <stdio.h>

Thread::Thread() {
    _thid = 0;
    _isRunning = false;
}

Thread::~Thread() {

}

void Thread::start() {
    //在threadFunc函数中会调用成员函数run方法，因此这里必须传一个this
    int ret = pthread_create(&_thid, nullptr, threadFunc, this);
    if(ret) {
        perror("pthread_create");
        return;
    }
    _isRunning = true;
}

void Thread::join() {
    if(_isRunning) {
        int ret = pthread_join(_thid, nullptr);
        if(ret) {
            perror("pthread_join");
            return;
        }
        _isRunning = false;
    }
}

//该静态函数要调用成员函数run方法，需要一个this指针
void *Thread::threadFunc(void *arg) {
    Thread *pth = static_cast<Thread *>(arg);
    if(pth) {
        pth->run();
    }
    /* return nullptr; */
    //或者不返回，等待线程结束
    pthread_exit(nullptr);
}









