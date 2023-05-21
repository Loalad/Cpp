#ifndef __PRODUCER_H__
#define __PRODUCER_H__

#include "thread.h"
#include "taskQueue.h"
#include <stdlib.h>
#include <iostream>
#include <unistd.h>

using std::cout;
using std::endl;

class Producer:public Thread {
public:
    Producer(TaskQueue &taskQue):_taskQue(taskQue) {

    }

    ~Producer() {

    }

    void run() override {
        ::srand(::clock());
        //这里不需要考虑上锁解锁
        //在TaskQueue里已经考虑了
        int cnt = 20;
        while(cnt--) {
            int number = rand() % 100;
            _taskQue.push(number);
            cout << ">>Producer number = " << number << endl;
            sleep(1);
        }
    }
private:
    TaskQueue &_taskQue;
};



#endif

