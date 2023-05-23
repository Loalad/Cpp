#include "TaskQueue.h"


TaskQueue::TaskQueue(size_t queSize)
:_queue()
,_queSize(queSize) 
,_mutex()
,_notEmpty(_mutex)
,_notFull(_mutex)
,_flag(true) {

}
TaskQueue::~TaskQueue() {

}

bool TaskQueue::empty() {
    return _queue.size() == 0;
}

bool TaskQueue::full() {
    return _queue.size() == _queSize;
}

void TaskQueue::push(ElemType ptask) {
    //自动控制解锁
    MutexLockGuard autoLock(_mutex);
    
    while(full()) {
        _notFull.wait();//执行的是pthread_cond_wait
    }

    _queue.push(ptask);

    _notEmpty.notify();
}

ElemType TaskQueue::pop() {
    //自动控制解锁
    MutexLockGuard autoLock(_mutex);

    while(empty() && _flag) {    //虚假唤醒
        _notEmpty.wait();
    }
    
    if(_flag) {
        ElemType tmp = _queue.front();
        _queue.pop();

        _notFull.notify();

        return tmp;
    }
    else {
        return nullptr;
    }
}

void TaskQueue::wakeup() {
    _flag = false;
    _notEmpty.notifyAll();
}
