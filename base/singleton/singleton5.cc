/*
**单例对象能自动回收：程序退出时自动调用destory方法
**方案三：atexit + pthread_once
**atexit注册的函数会在程序结束时调用
**调用的顺序遵循栈结构
*/
#include <pthread.h>

#include <iostream>
using std::cout;
using std::endl;

class Singleton{
public:
	//在多线程环境下，是线程安全的
	static Singleton * getInstance(){
		//pthread_once函数可以保证在多线程环境下，
		//init函数只会被执行一次
		pthread_once(&_once, init);
		return _pInstance;
	}

    //只会执行一次
	static void init(){
		_pInstance = new Singleton;
		atexit(destroy);
	}

	//如果程序退出时，能自动调用destroy方法，也能解决该问题
	static void destroy(){
		if(_pInstance) {
			delete _pInstance;
			_pInstance = nullptr;
		}
	}

private:
	Singleton() {	cout << "Singleton()" << endl;	}
	~Singleton() {	cout << "~Singleton()" << endl;	}

private:
	static Singleton * _pInstance;
	static pthread_once_t _once;
	int _data;
};

Singleton *Singleton::_pInstance = nullptr;//懒汉模式
pthread_once_t Singleton::_once = PTHREAD_ONCE_INIT;

 
void test1() {
	Singleton * p1 = Singleton::getInstance();
	Singleton * p2 = Singleton::getInstance();
	cout << "p1:" << p1 << endl;
	cout << "p2:" << p2 << endl;
} 
 
int main(void){
	test1();
	return 0;
}