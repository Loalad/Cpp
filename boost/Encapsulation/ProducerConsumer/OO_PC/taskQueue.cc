#include "taskQueue.h"


TaskQueue::TaskQueue(size_t queSize)
: _queSize(queSize)
, _que()
, _mutex()
, _notEmpty(_mutex)
, _notFull(_mutex) {

}

TaskQueue::~TaskQueue() {

}

bool TaskQueue::empty() {
    return _que.size() == 0;
}

bool TaskQueue::full() {
    return _que.size() == _queSize;
}

void TaskQueue::push(const int &value) {
    MutexLockGuard autoLock(_mutex);
    /* _mutex.lock(); */

    while(full()) {
        _notFull.wait();
    }

    _que.push(value);

    _notEmpty.notify();

    /* _mutex.unlock(); */
}

int TaskQueue::pop() {
    MutexLockGuard autoLock(_mutex);
    /* _mutex.lock(); */

    while(empty()) {
        _notEmpty.wait();
    }

    int ret = _que.front();
    _que.pop();

    _notFull.notify();

    /* _mutex.unlock(); */

    return ret;
}
