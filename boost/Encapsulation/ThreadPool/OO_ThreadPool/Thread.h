#ifndef __THREAD_H__
#define __THREAD_H__

#include <pthread.h>

class Thread {
public:
    Thread();
    ~Thread();
    
    void start();
    void join();

    static void *threadFunc(void *);
    virtual void run() = 0;

private:
    pthread_t _thid;    
    bool _isRunning;
};



#endif

