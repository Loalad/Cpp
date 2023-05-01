/*
**单例对象能自动回收
**AutoRelease放在全局区
*/
#include <iostream>

using std::cout;
using std::endl;

class Singleton{
    friend class AutoRelease;
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
    int _data;
};

Singleton *Singleton::_pInstance = nullptr;

class AutoRelease{
public:
    AutoRelease(Singleton *p):_p(p){
        cout << "AutoRelease构造函数" << endl;
    }
    ~AutoRelease(){
        cout << "AutoRelease析构函数" << endl;
        if(_p){
            delete _p;
            _p = nullptr;
        }
    }
    private:
    Singleton *_p;
};

void test1(){
    AutoRelease au(Singleton::getInstance());//au在test1函数栈空间销毁时调用析构函数
    Singleton *p1 = Singleton::getInstance();
    Singleton *p2 = Singleton::getInstance();
    cout << "p1:" << p1 << endl;
    cout << "p2:" << p2 << endl;
}

int main(){
    test1();
    return 0;
}