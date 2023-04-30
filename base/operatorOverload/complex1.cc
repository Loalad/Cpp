 /*运算符重载
 **1、成员函数进行重载（对象本身发生了变化）（+=）（++/--）
 **2、普通函数的友元进行重载（对象未发生变化）（+）
 */
#include <iostream>
using std::cout;
using std::endl;

class Complex {
    friend Complex operator+(const Complex &lhs, const Complex &rhs);
    friend Complex &operator+=(Complex &lhs, const Complex &rhs);
public:
    Complex(double real, double image) : _real(real), _image(image) {
        cout << "构造函数" << endl;
    }

    //1、成员函数进行重载
    //非成员函数第一个参数是this指针，代表左操作数
    Complex operator+(const Complex &rhs){
        cout << "成员函数重载+" << endl;
        return Complex(_real + rhs._real, _image + rhs._image);
    }
    Complex &operator+=(const Complex &rhs){
        cout << "成员函数重载+=" << endl;
        _real += rhs._real;
        _image += rhs._image;
        return *this;
    }
    Complex &operator++(){
        cout << "成员函数重载前置++" << endl;
        ++_real;
        ++_image;
        return *this;
    }
    Complex operator++(int){
        cout << "成员函数重载后置++" << endl;
        Complex tmp(*this);
        ++_real;
        ++_image;
        return tmp;
    }

    void print() {
        cout << _real;
        if (_image > 0) {
            if (_image == 1) cout << "+" << "j" << endl;
            else cout << "+" << _image << "j" << endl;
        } else if (_image == 0) cout << endl;
        else {
            if (_image == -1) cout << "-" << "j" << endl;
            else cout << "-" << (-1) * _image << "j" << endl;
        }
    }

private:
    double _real;
    double _image;
};

// //2、普通函数友元进行重载
// Complex operator+(const Complex &lhs, const Complex &rhs){
//     cout << "普通函数友元重载+" << endl;
//     return Complex(lhs._real + rhs._real, lhs._real + rhs._image);
// }
// Complex &operator+=(Complex &lhs, const Complex &rhs){
//     cout << "普通函数友元重载+=" << endl;
//     lhs._real += rhs._real;
//     lhs._image += rhs._image;
//     return lhs;
// }

void test1(){
    Complex c1(1, 2);
    Complex c2(2, 3);
    //Complex c3 = c1 + c2;
    //c1 += c2;
    c1++;
    c1.print();
    ++c1;
    c1.print();
}

int main(){
    test1();
    return 0;
}