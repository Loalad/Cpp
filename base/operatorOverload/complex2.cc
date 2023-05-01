 /*运算符 << 重载
 **可以达到 cout << c1(自定义类型) 的目的
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