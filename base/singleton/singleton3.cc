/*
**单例对象能自动回收
**方案一：嵌套类 + 静态对象
**AutoRelease类专为Singleton而生
**可以将其设计为嵌套类
**_ar静态对象在程序退出时，会自动调用销毁，此时执行析构函数，回收堆空间
*/
#include <iostream>

using std::cout;
using std::endl;

class Singleton{
    class AutoRelease{
    public:
        AutoRelease(){
            cout << "AutoRelease构造函数" << endl;
        }
        ~AutoRelease(){
            cout << "AutoRelease析构函数" << endl;
            if(_pInstance){
                delete _pInstance;
                _pInstance = nullptr;
            }
        }
    };
public:
    static Singleton *getInstance(){
        if(nullptr == _pInstance){
            _pInstance = new Singleton();
        }    
        return _pInstance;
    }
    static void destory(){
        if(_pInstance){
            delete _pInstance;
            _pInstance = nullptr;
        }
    }
private:
    Singleton() {    cout << "构造函数" << endl; }
    ~Singleton(){   cout << "析构函数" << endl;  }

private:
    static Singleton *_pInstance;
    static AutoRelease _ar;
    int _data;
};

Singleton *Singleton::_pInstance = nullptr;
Singleton::AutoRelease Singleton::_ar;

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