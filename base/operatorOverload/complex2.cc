 /*运算符重载
 **1、成员函数进行重载（对象本身发生了变化）（+=）（++/--）
 **2、普通函数的友元进行重载（对象未发生变化）（+）(>/<)
 */
#include <iostream>
using std::cout;
using std::endl;

class Complex {
    friend std::ostream &operator<<(std::ostream &os, const Complex &rhs);
public:
    Complex(double real, double image) : _real(real), _image(image) {
        cout << "构造函数" << endl;
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

std::ostream &operator<<(std::ostream &os, const Complex &rhs){
    os << rhs._real;
    if (rhs._image > 0) {
        if (rhs._image == 1) os << "+" << "j" << endl;
        else os << "+" << rhs._image << "j" << endl;
    } else if (rhs._image == 0) os << endl;
    else {
        if (rhs._image == -1) os << "-" << "j" << endl;
        else os << "-" << (-1) * rhs._image << "j" << endl;
    }
}

void test1(){
    Complex c1(1, 2);
    cout << "c1:" << c1;
}

int main(){
    test1();
    return 0;
}