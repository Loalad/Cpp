#include <iostream>

using std::cout;
using std::endl;
using std::string;
/*构造函数
**1、string();//默认构造函数，生成一个空字符串
**2、string(const char *rhs);//通过c风格字符串构造一个string对象
**3、string(const char *rhs, size_type count);//通过rhs的前count个字符构造一个string对象
**4、string(const string &rhs);//复制拷贝构造函数
**5、string(size_type count, char ch);//生成一个string对象，该对象包含count个ch字符
**6、string(InputIt first, InputIt last);//以区间[first, last)内的字符创建一个string对象
*/

/*增强for循环
**for(数据类型 变量名 :遍历的目标)
*/

/*
**将c++风格的字符串转换成c风格字符串（s.c_str()）
*/


int main(){
    string s1;
    cout << "s1:" << endl;

    string s2("hello world");
    cout << "s2:" << s2 << endl;

    //将s2前5个字符截掉
    string s3(s2, 5);
    cout << "s3:" << s3 << endl;
    //保留c风格字符串的前5个字符
    string s4("hello world", 5);
    cout << "s4:" << s4 << endl;

    string s5(5, 'a');
    cout << "s5:" << s5 << endl;

    //c++11后：增强for循环
    //auto表示自动进行类型推导
    // ：是一个分隔符
    cout << "遍历s4:";
    for(auto ch : s2){
        cout << ch << " ";
    }
    cout << endl;

    //截取子串
    string s6 = s2.substr(1,6);//从下标为1的位置向后截6个字符
    cout << "s6:" << s6 << endl;

    //将c++风格字符串转换成c风格字符串
    const char *pstr = s2.c_str();//只读
    cout << "pstr:" << pstr << endl;

    //string对象的首地址和字符串内容的首地址
    cout << "s2对象的首地址为：" << &s2 << endl;
    printf("s2字符串内容的首地址为：%p\n", s2.c_str());

    return 0;
}