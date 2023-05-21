#ifndef __
#define __

#include <pthread.h>

//数据成员是引用，可以只有类的前向声明(因为不需要构造)
//数据成员是对象，则必须引用头文件（需要构造这个类的对象）
class MutexLock;

class Condition {
public:
    Condition(MutexLock &mutex);
    ~Condition();
    void wait();
    void notify();
    void notifyAll();

private:
    pthread_cond_t _cond;
    MutexLock &_mutex;
};


#endif

