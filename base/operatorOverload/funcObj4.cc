/*
**std::function和std::bind
*/

#include <iostream>
#include <functional>

using std::cout;
using std::endl;
using std::function;
using namespace std::placeholders;

void print(){
    cout << "print()" << endl;
}

void display(){
    cout << "display()" << endl;
}

typedef void(*func)();

struct Foo{
    void show(){
        cout << "Foo::show()" << endl;
    }

    void exhibit(int x){
        cout << "exhibit'x = " << x << endl; 
    }
    void display(int x, int y){
        cout << "成员函数display() x:" << x << ", y:" << y << endl;
    }
};

void show(int x, int y){
    cout << "普通show() x:" << x << ", y:" << y << endl;
}

void test1(){
    function<void()> f = print;//尖括号内void为返回值类型，（）里是参数列表
    f();

    f = display;
    f();

    func f0 = print;
    f = f0;//f0是函数指针，交给一个函数对象(它可以是函数、函数指针、成员函数指针、函数对象)
    f();

    //f = &Foo::show;//错误：对象f是没有参数的，但成员函数show有隐含的this指针
    //对于成员函数的this指针，需要提前绑定
    //对于bind函数，第二个参数是this指针（可以是1、对象，也可以是2、指针）
    //1、
    f = std::bind(&Foo::show, Foo());//第二个参数是绑定的对象（匿名对象）相当于this
    f();

    //2、
    Foo *pf = nullptr;
    f = std::bind(&Foo::show, pf);
    f();

    f = std::bind(&Foo::exhibit, pf, 1);//?????
    f();

    f = std::bind(show, 1, 2);
    f();

    //使用占位符 std::placeholders::_1 ...
    std::function<void(int)> f2 = std::bind(show, 3, _1);
    f2(4);

    f2 = std::bind(show, _1, 5);
    f2(6);

    std::function<void(int, int)> f3 = show;
    f3(7, 8);

    f3 = std::bind(&Foo::display, Foo(), _1, _2);
    f3(9, 10);

    //占位符的数字代表参数传递时实参的位置
    //占位符本身所在的位置代表形参的位置   即传过去是（12， 11）
    f3 = std::bind(&Foo::display, Foo(), _2, _1);
    f3(11, 12);



}

int main(){
    test1();
    return 0;
}