/*
**流的状态
**重置流的状态clear和ignore函数（注意这个的用法（第30行））
*/
#include <iostream>

using std::cin;
using std::cout;
using std::endl;
using std::string;

void printStreamStatus(std::istream &is) {
    cout << "is's goodbit:" << is.good() << endl;
    cout << "is's badbit:" << is.bad() << endl;
    cout << "is's failbit:" << is.fail() << endl;
    cout << "is's eofbit:" << is.eof() << endl;
}

#include <limits>
void readInteger(int &num) {
    cout << "请输入整型数据" << endl;
    // 逗号表达式：它的返回值只与最后一个表达式有关
    while (cin >> num, !cin.eof()) {
        if (cin.bad()) {
            cout << "输入流已损坏" << endl;
            return;
        } else if (cin.fail()) {
            cin.clear();
            //重点--丢弃多少个字节
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cout << "请输入有效整型数据" << endl;
            continue;
        } else {
            cout << "num:" << num << endl;
            break;
        }
    }
}

void test2() {
    int number = 0;
    readInteger(number);
    cout << "number:" << number << endl;
}

void test1() {
    int num = 0;
    printStreamStatus(cin);
    cin >> num;
    printStreamStatus(cin);
    cout << "num:" << num << endl;

    cin.clear();
    cin.ignore(1024, '\n');
    cout << "重置流的状态" << endl;
    printStreamStatus(cin);

    string s1;
    cin >> s1;
    cout << "s1:" << s1 << endl;
}
int main() {
    //test1();
    test2();

    return 0;
}