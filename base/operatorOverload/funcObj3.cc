/*成员函数指针
**指向成员函数的指针对象（用一个指针指向类的成员函数）
** (.*和->*)
*/
#include <iostream>

using std::cout;
using std::endl;
 
struct Foo{
    void display(int y){
        cout << "y:" << y << endl;
    }
    void print(int x){
        cout << "x:" << x << endl;
    }
};


//定义一个函数指针类型,返回值是void，参数列表为空
typedef void (*Function)();//普通函数指针

typedef void(Foo::*Func)(int);//定义了一个指向成员函数的指针类型Func
/*
**错误示例
**1、typedef void(*Func)(int)；
**2、typedef void(*Func)(Foo *const, int)；
*/

void test1(){
    /*Func f = &Foo::print;
    **这段代码定义了一个指向成员函数的指针变量 f，
    **并将其初始化为指向类 Foo 中名为 print 的成员函数的地址。
    */
    Func f = &Foo::print;
    /*
    **如果在定义成员函数指针时不加取地址符 &，就会出现编译错误，
    **因为成员函数指针需要指向函数的地址，而不是函数本身。
    **如果省略取地址符，编译器会将其解释为对成员函数的调用，而不是获取其地址。
    */


    /*
    **对于一个成员函数指针指向的成员函数
    **必须用一个对象进行调用（以下两种调用是错误的）
    **1、f();//这样调用是错误的，需要使用.*或者->*去访问
    **2、f->*();//f是一个指针，调用成员函数必须要用一个对象
    */
   Foo foo;

   /*
   **foo.f的意思是调用foo里的名为f的成员函数
   **为了表示f是一个指针，在前面加一个解引用（*），
   **并把foo.*f用括号括起来
   */
   (foo.*f)(1); 

   Foo *pf = &foo;
   f = &Foo::display;
   (pf->*f)(1);//57,59行与48，55行效果一样，只是调用的方式不同
}

int main(){
    test1();
    return 0;
}