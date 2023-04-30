/*
**1、Student1只能生成栈对象：把operaotr new函数放在private区
**2、Student2只能生成堆空间对象：把析构函数放在private区
*/

/*
？？？？如何回收堆空间的资源？？？？
*/
#include <string.h>

#include <iostream>
using std::cout;
using std::endl;

class Student1 {
public:
    Student1(int id, const char *name)
        : _id(id), _name(new char[strlen(name) + 1]()) {
        strcpy(_name, name);
        cout << "调用构造函数" << endl;
    }
    ~Student1() {
        delete[] _name;
        _name = nullptr;
        cout << "调用析构函数" << endl;
    }
    void print() {
        cout << "id:" << _id << endl;
        cout << "_name:" << _name << endl;
    }
    void operator delete(void *p) {
        cout << "调用operator delete函数" << endl;
        free(p);
    }

private:
    void *operator new(size_t sz) {
        cout << "调用operaotr new函数" << endl;
        return malloc(sz);
    }

private:
    int _id;
    char *_name;
};

class Student2 {
public:
    Student2(int id, const char *name)
        : _id(id), _name(new char[strlen(name) + 1]()) {
        strcpy(_name, name);
        cout << "调用构造函数" << endl;
    }

    void print() {
        cout << "id:" << _id << endl;
        cout << "_name:" << _name << endl;
    }
    void *operator new(size_t sz) {
        cout << "调用operaotr new函数" << endl;
        return malloc(sz);
    }
    void operator delete(void *p) {
        cout << "调用operator delete函数" << endl;
        free(p);
    }
    void destory(){
        //this->~Student2();
        delete[] this->_name;
        this->_name = nullptr;
        cout << "释放申请的堆空间" << endl;
    }

private:
    ~Student2() {
        delete[] _name;
        _name = nullptr;
        cout << "调用析构函数" << endl;
    }

private:
    int _id;
    char *_name;
};

int main() {
    // // Student1只能申请栈空间对象
    // Student1 s1(101, "zhangsan");
    // s1.print();
    // // Student1 *p = new Student1(101, "zhangsan");

    //Student2只能申请堆空间对象
    //Student2 s2(102, "lisi");
    Student2 *p = new Student2(102, "lisi");
    p->print();
    p->destory();//这里怎么回收

    return 0;
}