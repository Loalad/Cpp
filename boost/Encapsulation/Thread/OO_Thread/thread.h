//1、为了查看线程是否在运行，设置标志_isRunning
//2、注意start函数中会调用pthread_create函数
//  pthread_create函数会调用子线程入口函数threadFunc
//  若threadFunc函数是非static的
//  那么它的参数会有一个this指针，不满足子线程入口函数的定义
//3、线程入口函数会调用成员函数run方法，但他本身是个静态函数
//  因此必须将this指针作为参数传递给threadFunc函数
//  所以pthread_create函数的第四个参数是个this
#ifndef __THREAD_H__
#define __THREAD_H__

#include <pthread.h>


class Thread {
public:
    Thread();
    virtual ~Thread();

    void start();
    void join();

private:
    //pthread_create时第三个参数会调用threadFunc函数，
    //若不将其设置为静态函数，则参数会有隐含的this指针
    static void *threadFunc(void *);
    virtual void run() = 0;

private:
    pthread_t _thid;
    bool _isRunning;
};


#endif

