#include <iostream>
#include <sstream>
#include <fstream>

using std::cout;
using std::endl;
using std::istringstream;
using std::ostringstream;
using std::string;
using std::ifstream;

void test1() {
    /*
    **1、将整型数转换成字符串类型输出
    **2、将字符串类型转换成其他类型数据
    */

    // 1、
    int num1 = 1;
    int num2 = 2;

    ostringstream oss;

    // 功能类似于sprintf
    oss << "num1 = " << num1 << " num2 = " << num2;
    cout << oss.str() << endl;

    // 2、
    num1 = 10;
    num2 = 20;
    cout << "修改num1和num2" << endl;

    string line = oss.str();
    string word1, word2;

    // 将字符串line放入输入流中
    istringstream iss(line);
    //前提条件：知道数据的格式
    iss >> word1 >> num1 >> word2 >> num2;
    cout << "num1:" << num1 << endl;
    cout << "num2:" << num2 << endl;
}

void readConfig(const char *filename){
    ifstream ifs(filename);
    if(!ifs){
        cout << "ifstream read " << filename << " error" << endl;
        return;
    }

    string line;
    string key, value;
    while(std::getline(ifs, line)){
        istringstream iss(line);
        iss >> key >> value;
        cout << key << "-->" << value << endl;
    }
    ifs.close();
}

int main() {
    //test1();
    readConfig("server.conf");
    return 0;
}