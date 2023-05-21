//1、为了查看线程是否在运行，设置标志_isRunning
//2、注意start函数中会调用pthread_create函数
//  pthread_create函数会调用子线程入口函数threadFunc
//  若threadFunc函数是非static的
//  那么它的参数会有一个this指针，不满足子线程入口函数的定义
#ifndef __THREAD_H__
#define __THREAD_H__

#include <pthread.h>
#include <functional>

using std::function;
using std::bind;


class Thread {
    using ThreadCallback = function<void()>;
public:
    Thread(ThreadCallback &&cb);
    virtual ~Thread();

    void start();
    void join();

private:
    //pthread_create时第三个参数会调用threadFunc函数，
    //若不将其设置为静态函数，则参数会有隐含的this指针
    static void *threadFunc(void *);

private:
    pthread_t _thid;
    bool _isRunning;
    ThreadCallback _cb;//存任务
};


#endif

