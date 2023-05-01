/*单例模式实现
**1、禁止从类外调用构造函数，则将构造函数私有化
**2、只能通过从类内创建对象，通过一个函数实现
**3、将创建对象的函数设置为static，否则需要一个对象来调用该函数
**4、由于static方法只能访问static成员变量，因此需要static数据成员
**5、由于该函数只能被调用一次，因此需要进行判断
**6、为了避免对象被拷贝构造或者赋值运算符，需将它们私有化或者从类中删除（=delete）
*/
#include <iostream>

using std::cout;
using std::endl;

class Singleton{
public:
    static Singleton *getInstance(){
        if(nullptr == _pinstance){
            _pinstance = new Singleton();
        }
        return _pinstance;
    }
    static void destory(){
        if(nullptr == _pinstance){
            delete _pinstance;
            _pinstance = nullptr;
        }
    }

private:
    Singleton(){
        cout << "调用构造函数" << endl;
    }

    Singleton(const Singleton &rhs) = delete;
    Singleton &operator=(const Singleton &rhs) = delete;

static Singleton *_pinstance;
};

Singleton *Singleton::_pinstance = nullptr;

int main(){
    Singleton *p1 = Singleton::getInstance();
    cout << "p1的地址为：" << p1 << endl;

    Singleton *p2 = Singleton::getInstance();
    cout << "p2的地址为：" << p2 << endl;

    //Singleton s = *p1;//报错
    p1->destory();
    
    return 0;
}