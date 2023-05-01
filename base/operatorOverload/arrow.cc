/*
**重载指针访问运算符和解引用运算符
**调用指针访问运算符，返回另一个对象的指针
**调用解引用运算符，返回另一个对象
*/
/*
**智能指针的雏形RAII技术（依赖于重载上述两个运算符）
**MiddleLayer内部重载了上述两个运算符，
**就是为了将对象转换为另外一个对象
*/
#include <iostream>
using std::cout;
using std::endl;

class Data{
public:
    Data(){ cout << "Data构造函数" << endl; }
    ~Data(){ cout << "Data析构函数" << endl; }

    int getLength()const{
        return 10;
    }

    int _data = 1;
};

class MiddleLayer{
public:
    //在构造函数中托管堆空间的对象Data
    MiddleLayer(Data *pdata):_pdata(pdata){
        cout << "MiddleLayer构造函数" << endl;
    }

    //箭头运算符的重载
    Data *operator->(){
        return _pdata;
    }
    //解引用运算符的重载
    Data &operator*(){
        return *_pdata;
    }

    //在析构函数中，回收托管的堆空间对象Data
    ~MiddleLayer(){
        cout << "MiddleLayer析构函数" << endl;
        if(_pdata){
            delete _pdata;
            _pdata = nullptr;
        }
    }

private:
    Data *_pdata;
};

void test(){
    /*
    **ml本身是一个对象，但其使用像一个指针
    **这是智能指针的雏形-->可以自动释放堆空间对象，RAII技术（依赖于重载两个运算符）
    */
    MiddleLayer ml = new Data();
    /*
    **MiddleLayer里并没有getLength方法
    **但是重载了->运算符，返回了一个Data类型的指针
    **该指针可以调用Data中的getLength方法
    **相当于(m.operator->())->getLength()
    */
    cout << ml->_data << endl;
    cout << ml->getLength() << endl;//简化操作
    cout << (ml.operator->())->getLength() << endl;//完整形式

    cout << (*ml).getLength() << endl;    
    cout << (ml.operator*()).getLength() << endl;
}

int main(){
    test();
    return 0;
}