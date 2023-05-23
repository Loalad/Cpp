#include "Task.h"
#include "ThreadPool.h"
#include <iostream>

using std::cout;
using std::endl;


class MyTask: public Task {
public:
    void process() override {
        ::srand(::clock());
        int number = ::rand() % 100;
        cout << " MyTask number = " << number << endl;
    }
};


int main() {
    unique_ptr<Task> ptask(new MyTask());

    ThreadPool pool(4, 10);
    pool.start();

    int cnt = 20;
    while(cnt--) {
        pool.addTask(ptask.get());
    }
    /* cout << "cnt = " << cnt << endl; */


    pool.stop();
    return 0;
}

