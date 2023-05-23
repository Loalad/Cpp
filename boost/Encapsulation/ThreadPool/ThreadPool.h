#ifndef __THREADPOOL_H__
#define __THREADPOOL_H__

#include "TaskQueue.h"
#include <vector>
#include <memory>
/* #include "Thread.h" */

using std::vector;
using std::unique_ptr;

class Thread;

class ThreadPool {
    friend class WorkThread;
public:
    ThreadPool(size_t threadNum, size_t queSize);
    ~ThreadPool();

    void start();
    void stop();

    void addTask(Task *ptask);

private:
    Task * getTask();

    void threadFunc();

private:
    size_t _threadNum;
    size_t _queSize;//任务队列
    vector<unique_ptr<Thread>> _threads;
    TaskQueue _taskQue;
    bool _isExit;

};



#endif

