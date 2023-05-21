#include "taskQueue.h"
#include "producer.h"
#include "consumer.h"
#include <iostream>

using std::cout;
using std::endl;

void test0() {
    TaskQueue taskQue(10);

    Producer pro(taskQue);
    Consumer con(taskQue);

    pro.start();
    con.start();

    pro.join();
    con.join();
}

int main() {
    test0();
    return 0;
}

