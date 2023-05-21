#include "thread.h"
#include <iostream>
#include <unistd.h>
#include <memory>

using std::cout;
using std::endl;
using std::unique_ptr;

class MyThread: public Thread {
public:
    void run() override {
        while(1) {
            cout << "MyThread is running!" << endl;
            sleep(1);
        }
    }
    ~MyThread() {}
};

void test() {
    MyThread myth;
    myth.start();
    myth.join();
}

void test1() {
    unique_ptr<MyThread> pth(new MyThread());
    pth->start();
    pth->join();
}

int main() {
    test1();

    return 0;
}

