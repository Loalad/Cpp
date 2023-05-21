#ifndef __CONSUMER_H__
#define __CONSUMER_H__

#include "thread.h"
#include "taskQueue.h"
#include <stdlib.h>
#include <iostream>
#include <unistd.h>

using std::cout;
using std::endl;

class Consumer:public Thread {
public:
    Consumer(TaskQueue &taskQue):_taskQue(taskQue) {

    }

    ~Consumer() {

    }

    void run() override {
        ::srand(::clock());
        //这里不需要考虑上锁解锁
        //在TaskQueue里已经考虑了
        int cnt = 20;
        while(cnt--) {
            int ret = _taskQue.pop();
            cout << ">>Consumer number = " << ret << endl;
            sleep(1);
        }
    }
private:
    TaskQueue &_taskQue;
};



#endif

