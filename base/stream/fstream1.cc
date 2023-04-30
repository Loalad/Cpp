#include <string.h>

#include <fstream>
#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::fstream;
using std::ifstream;
using std::ofstream;
using std::string;
using std::vector;

void test1() {
    ifstream ifs("fstream1.cc");
    if (!ifs.good()) {
        cout << "ifstream 打开失败" << endl;
        return;
    }

    string str;
    // 输入流运算符默认是用空格 \t 进行分割
    while (ifs >> str) {
        cout << str << endl;
    }

    ifs.close();
}

void test2() {
    /*
    **ifs.getline读取一行数据
    **需要准备一个buf
    **通过流对象自带的getline方法完成的，具有局限性，
    **每次只能读取1024个字节，当一行超过1024则无法完成
    */
    ifstream ifs("fstream1.cc");
    if (!ifs.good()) {
        cout << "ifstream 打开失败" << endl;
        return;
    }

    // 每次读取一行数据
    char buf[1024] = {0};
    while (ifs.getline(buf, sizeof(buf))) {
        cout << buf << endl;
    }

    ifs.close();
}

void test3() {
    /*
    **为解决上述局限
    **可调用std::getline
    */
    ifstream ifs("fstream1.cc");
    if (!ifs.good()) {
        cout << "ifstream 打开失败" << endl;
        return;
    }

    // 每次读取一行数据,换行符不会写入line-->输出全在一行
    string line;
    while (std::getline(ifs, line)) {
        cout << line;
    }

    ifs.close();
}

void test4() {
    /*
    **获取了一行数据后，将数据存入容器中
    */
    ifstream ifs("fstream1.cc");
    if (!ifs.good()) {
        cout << "ifstream 打开失败" << endl;
        return;
    }

    vector<string> fileVec;
    // 每次读取一行数据,换行符不会写入line-->输出全在一行
    string line;
    while (std::getline(ifs, line)) {
        fileVec.push_back(line);
    }

    for (auto &s : fileVec) {
        cout << s << endl;
    }

    ifs.close();
}

void test5() {
    /*
    **1、文件输出流不要求文件存在
    **当没有文件时，会新建一个文件（默认文件模式是out）
    **但文件存在时，会清空文件的内容
    **2、往文件中写入还可以使用write方法（ofs.write）
    */

    // //默认文件模式是out-->会把原文件的内容清空再写入
    // ofstream ofs("test.txt");
    // if (!ofs) {
    //     cout << "ofstream 打开失败" << endl;
    //     return;
    // }

    // 修改文件模式为app-->在文件末尾追加
    ofstream ofs("test.txt", std::ios::app);
    if (!ofs) {
        cout << "ofstream 打开失败" << endl;
        return;
    }

    string line("this is a new line\n");
    ofs << line;  // 将line写入ofs(文件)

    const char *pstr = "hello world\n";
    ofs.write(pstr, strlen(pstr));

    ofs.close();
}

void test6() {
    /*
    **读取指定的字符长度read
    */
    ifstream ifs("fstream1.cc");
    if (!ifs.good()) {
        cout << "ifstream 打开失败" << endl;
        return;
    }

    // 获取文件长度
    ifs.seekg(0, std::ios::end);
    size_t length = ifs.tellg();
    cout << "文件长度为" << length << endl;

    char *pbuf = new char[length + 1];
    ifs.seekg(0, std::ios::beg);  // 偏移到文件的起始位置
    ifs.read(pbuf, length);

    string content(pbuf);
    delete[] pbuf;

    cout << "内容为" << content << endl;

    ifs.close();
}

void test7() {
    /*
    **文件输入输出流：要求文件必须要存在
    **需求：先从终端获取数据，写入文件；
    **     再从该文件中读出这些数据
    */
    fstream fs;
    fs.open("test2.txt");//要求文件必须存在，否则出错
    if (!fs) {
        cout << "fstream 打开失败" << endl;
        return;
    }

    int num = 0;
    //从终端中读取数据到文件
    for(int i = 0; i < 5; ++i){
        std::cin >> num;
        fs << num << " ";
    }

    size_t pos = fs.tellg();
    cout << "pos:" << pos << endl;
    fs.seekg(0);//偏移到文件开始位置

    cout << num << endl;

    //从文件中读取数据
    for(int i = 0; i < 5; ++i){
        fs >> num;
        cout << num << " ";
    }
    cout << endl;

    fs.close();
}

int main() {
    test7();
    return 0;
}