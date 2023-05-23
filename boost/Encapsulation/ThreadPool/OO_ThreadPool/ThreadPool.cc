#include "ThreadPool.h"
#include "WorkThread.h"
#include "Task.h"
#include <unistd.h>

ThreadPool::ThreadPool(size_t threadNum, size_t queSize) 
: _threadNum(threadNum)
, _queSize(queSize)
, _taskQue(queSize)
, _isExit(false) {}

ThreadPool::~ThreadPool() {}

void ThreadPool::start() {
    //创建子线程，并放入vector
    for(size_t i = 0; i < _threadNum; ++i) {
        unique_ptr<Thread> up(new WorkThread(*this));//WorkThread的构造函数需要一个ThreadPool对象
        _threads.push_back(std::move(up));
    }

    //遍历vector，将所有子线程运行起来
    for(auto &elem : _threads) {
        elem->start();
    }
}

void ThreadPool::stop() {
    //在退出前把任务队列中的任务执行完再退出
    while(!_taskQue.empty()) {
        sleep(1);
    }

    _isExit = true;
    _taskQue.wakeup();
    for(auto &elem : _threads) {
        elem->join();
    }
}

void ThreadPool::addTask(Task *ptask) {
    if(ptask) {
        _taskQue.push(ptask);
    }
}

Task *ThreadPool::getTask() {
    return  _taskQue.pop();
}

void ThreadPool::threadFunc() {
    //只要线程池不退出，就一直拿任务-执行任务
    //在stop函数中将——isExit设置为true，中间的时间差可能使gettask->pop函数阻塞
    while(!_isExit) {
        Task *ptask = getTask();
        if(ptask) {
            ptask->process();
        }
        /* sleep(3); */
    }
}
