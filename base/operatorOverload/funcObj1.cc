#include <iostream>

using std::cout;
using std::endl;

class Foo{
public:
    int operator()(int x, int y){
        ++_count;
        return x * y;
    }
    int operator()(int x, int y, int z){
        ++_count;
        return x + y + z;
    }

    int _count = 0;//状态
};

void test1(){
    Foo foo;
    cout << foo(1, 2) << endl;
    cout << "foo._count" << foo._count << endl;
}

int main(){
    test1();//test1看成一个对象，（）是一个函数调用
    return 0;
}