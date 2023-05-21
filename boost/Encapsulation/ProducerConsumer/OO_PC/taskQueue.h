#ifndef __TASKQUEUE_H__
#define __TASKQUEUE_H__

#include <queue>
#include "mutexLock.h"
#include "condition.h"

using std::queue;

class TaskQueue {
public:
    TaskQueue(size_t quqSize);
    ~TaskQueue();
    bool empty();
    bool full();
    void push(const int &value);
    int pop();

private:
    size_t _queSize;
    queue<int> _que;
    MutexLock _mutex;
    Condition _notEmpty;
    Condition _notFull;
};



#endif

