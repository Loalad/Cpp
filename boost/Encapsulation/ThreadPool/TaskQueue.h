#ifndef __TASKQUEUE_H__
#define __TASKQUEUE_H__

#include <queue>
#include "MutexLock.h"
#include "Condition.h"

using std::queue;

class Task;
using ElemType = Task *;

class TaskQueue {
public:
    TaskQueue(size_t quesize);
    ~TaskQueue();

    bool empty();
    bool full();
    void push(ElemType ptask);
    ElemType pop();

    //将所有在_notEmpty上的线程全部唤醒
    void wakeup();

private:
    queue<ElemType> _queue;
    size_t _queSize;
    MutexLock _mutex;
    Condition _notEmpty;
    Condition _notFull;
    bool _flag;
};




#endif

