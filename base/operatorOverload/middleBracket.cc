#include <iostream>
#include <string.h>
using std::cout;
using std::endl;

class CharArray{
public:
    CharArray(size_t sz = 10):_data(new char[sz + 1]()){
        cout << "构造函数" << endl;
    }

    char &operator[](size_t idx){
        cout << "下标访问运算符" << endl;
        return _data[idx];
    }

    size_t length()const{
        return strlen(_data);
    }

    ~CharArray(){
        cout << "析构函数" << endl;
        if(_data){
            delete []_data;
            _data = nullptr;
        }
    }

private:
    char *_data;
};

void test1(){
    //将arr看成对象
    int arr[5] = {1, 2, 3, 4, 5};
    cout << arr[0] << endl;
    //arr.operator[](0)

    const char *pstr = "hello world";
    CharArray carr(strlen(pstr));

    for(size_t idx = 0; idx < strlen(pstr); ++idx){
        carr[idx] = pstr[idx];//这里要求第12行返回必须是一个引用
    }

    for(size_t idx = 0; idx < carr.length(); ++idx){
        cout << carr[idx] << " ";
    }
    cout << endl;

}

int main(){
    test1();
    return 0;
}