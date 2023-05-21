#include "thread.h"
#include <iostream>
#include <unistd.h>

using std::cout;
using std::endl;

class MyTask {
public:
    void process(int) {
        while(1) {
            cout << "MyTask is running!" << endl;
            sleep(1);
        }
    }
};

void func(int x) {
    while(1) {
        cout << "func is running!" << endl;
        sleep(x);
    }
    
}

void test() {
    MyTask task;
    Thread th(bind(&MyTask::process, &task, 1));

    th.start();
    th.join();
}

void test1() {
    Thread th(bind(func, 1));

    th.start();
    th.join();
}

int main() {
    test1();
    return 0;
}

