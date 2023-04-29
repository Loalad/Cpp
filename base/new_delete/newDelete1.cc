/*new和delete表达式的实现步骤*/
#include <iostream>
#include <string.h>
using std::cout;
using std::endl;

class Student{
public:
    Student(int id, const char *name):_id(id), _name(new char[strlen(name) + 1]()){
        strcpy(_name, name);
        cout << "调用构造函数" << endl;
    }
    ~Student(){
        delete []_name;
        _name = nullptr;
        cout << "调用析构函数" << endl;
    }
    void print(){
        cout << "id:" << _id << endl;
        cout << "_name:" << _name << endl;
    }
    void *operator new(size_t sz){
        cout << "调用operaotr new函数" << endl;
        return malloc(sz);
    }
    void operator delete(void *p){
        cout << "调用operator delete函数" << endl;
        free(p);
    }

private:
    int _id;
    char *_name;
};

int main(){
    Student *p = new Student(101, "zhangsan");
    p->print();
    delete p;

    return 0;
}