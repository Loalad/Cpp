/*
**单例对象能自动回收：程序退出时自动调用destory方法
**方案二：atexit + destory
**atexit注册的函数会在程序结束时调用
**调用的顺序遵循栈结构
*/
#include <iostream>

using std::cout;
using std::endl;

class Singleton{
public:
    //在多线程环境下线程不安全,可以在全局内就创建对象（38行）
    static Singleton *getInstance(){
        if(nullptr == _pInstance){
            _pInstance = new Singleton();
            atexit(destory);
        }    
        return _pInstance;
    }
    static void destory(){
        if(_pInstance){
            cout << "destory" << endl;
            delete _pInstance;
            _pInstance = nullptr;
        }
    }
private:
    Singleton() {    cout << "构造函数" << endl; }
    ~Singleton(){   cout << "析构函数" << endl;  }

private:
    static Singleton *_pInstance;
    int _data;
};

//前面有Singleton作用域
//getInstance()前可不加作用域
Singleton *Singleton::_pInstance = getInstance();//饱汉模式

void test1(){
    Singleton *p1 = Singleton::getInstance();
    Singleton *p2 = Singleton::getInstance();
    cout << "p1:" << p1 << endl;
    cout << "p2:" << p2 << endl;
}

int main(){
    test1();
    return 0;
}