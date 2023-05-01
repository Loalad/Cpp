/*
**函数指针
*/
#include <iostream>

using std::cout;
using std::endl;

typedef int Integer;

//定义一个函数指针类型,返回值是void，参数列表为空
typedef void (*Function)();//函数指针

//定义两个函数，它们的返回值类型和参数列表都与函数指针类型匹配
void display(){
    cout << "diaplay()" << endl;
}

void print(){
    cout << "print()" << endl;
}

void test1(){
    //Function是一个类型，f是一个对象
    Function f = display;   //声明一个函数指针变量并将其指向 display() 函数
    f();                    //通过函数指针变量调用 hello() 函数

    f = &print;//这里可以取地址也可以不取
    f();
}

int main(){
    test1();
    return 0;
}