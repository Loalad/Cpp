/*自己实现string*/
#include <iostream>
#include <string.h>

using std::cout;
using std::endl;

class String 
{
public:
	String() {
        _pstr = new char[1]();
        strcpy(_pstr, "");
        _size = 0;
        cout << "String()" << endl;
    }
	String(const char *str) {
        _pstr = new char[strlen(str) + 1]();
        strcpy(_pstr, str);
        _size = strlen(str);
        cout << "String(const char *)" << endl;
    }
	String(const String &rhs){
        _pstr = new char[rhs._size + 1]();
        strcpy(_pstr, rhs._pstr);
        _size = rhs._size;
        cout << "String(const String &)" << endl;
    }
	~String(){
        if(nullptr == _pstr){
            delete []_pstr;
            _pstr = nullptr;
        }
        cout << "~String()" << endl;
    }
	String &operator=(const String &str){
        _pstr = new char[str.size() + 1]();
        strcpy(_pstr, str._pstr);
        _size = str._size;
        cout << "operator=(const String &)" << endl;
    }
	String &operator=(const char *str){
        _pstr = new char[strlen(str) + 1]();
        strcpy(_pstr, str);
        _size = strlen(str);
        cout << "operator=(const char *)" << endl;
    }

	String &operator+=(const String &str){
        char *tmp = new char[_size + 1]();
        strcpy(tmp, _pstr);
        delete []_pstr;
        _pstr = new char[_size + str._size + 1]();
        strcpy(_pstr, tmp);
        strcat(_pstr, str._pstr);
        _size = strlen(_pstr);
        return *this;
    }
	String &operator+=(const char *str){
        char *tmp = new char[_size + strlen(str) + 1]();
        strcpy(tmp, _pstr);
        delete []_pstr;
        _pstr = new char[_size + strlen(str) + 1]();
        strcpy(_pstr, tmp);
        strcat(_pstr, str);
        _size = strlen(_pstr);
        return *this;
    }
	
	char &operator[](std::size_t index){
        return _pstr[index];
    }
	const char &operator[](std::size_t index) const;
	
	std::size_t size() const{
        return _size;
    }
	const char* c_str() const{
        return _pstr;
    }
	
	friend bool operator==(const String &, const String &);
	friend bool operator!=(const String &, const String &);
	
	friend bool operator<(const String &, const String &);
	friend bool operator>(const String &, const String &);
	friend bool operator<=(const String &, const String &);
	friend bool operator>=(const String &, const String &);
	
	friend std::ostream &operator<<(std::ostream &os, const String &s);
	friend std::istream &operator>>(std::istream &is, String &s);

    friend String operator+(const String &, const String &);
    friend String operator+(const String &, const char *);
    friend String operator+(const char *, const String &);

private:
	char *_pstr;
    size_t _size;
};

bool operator==(const String &lhs, const String &rhs){
    return !strcmp(lhs._pstr, rhs._pstr);
}
bool operator!=(const String &lhs, const String &rhs){
    return strcmp(lhs._pstr, rhs._pstr);
}
	
bool operator<(const String &lhs, const String &rhs){
    return (strcmp(lhs._pstr, rhs._pstr) < 0);
}
bool operator>(const String &lhs, const String &rhs){
    return (strcmp(lhs._pstr, rhs._pstr) > 0);
}
bool operator<=(const String &lhs, const String &rhs){
    return (strcmp(lhs._pstr, rhs._pstr) <= 0);
}
bool operator>=(const String &lhs, const String &rhs){
    return (strcmp(lhs._pstr, rhs._pstr) >= 0);
}
	
std::ostream &operator<<(std::ostream &os, const String &s){
    for(size_t i = 0; i < s._size; ++i){
        os << s._pstr[i];
    }
    return os;
}

String operator+(const String &lhs, const String &rhs){
    char *pstr = new char[lhs.size() + rhs.size() + 1]();
    strcpy(pstr, lhs._pstr);
    strcat(pstr, rhs._pstr);
    return String(pstr);
}
String operator+(const String &lhs, const char *rhs){
    char *pstr = new char[lhs.size() + strlen(rhs) + 1];
    strcpy(pstr, lhs._pstr);
    strcat(pstr, rhs);
    return String(pstr);
}
String operator+(const char *lhs, const String &rhs){
    char *pstr = new char[strlen(lhs) + rhs.size() + 1]();
    strcpy(pstr, lhs);
    strcat(pstr, rhs._pstr);
    return String(pstr);
}

int main(){
    String s1;
    cout << "s1:" << s1 << endl;

    String s2("hello");
    cout << "s2:" << s2 << endl;
    
    String s3 = s2;
    cout << "s3:" << s3 << endl;

    String s4;
    s4 = s2;
    cout << "s4:" << s4 << endl;

    String s5;
    s5 = "world";
    cout << "s5:" << s5 << endl;

    s4 += s5;
    cout << "s4:" << s4 << endl;

    s4 += "yy";
    cout << "s4:" << s4 << endl;

    cout << "s4[1]:" << s4[1] << endl;

    cout << "s4.c_str :" << s4.c_str() << endl;

    cout << "s2 == s3 :" << (s2 == s3) << endl;

    cout << "s2 != s3 :" << (s2 != s3) << endl;

    cout << "s3 < s4 :" << (s3 < s4) << endl;

    cout << "s3 > s4 :" << (s3 > s4) << endl;

    cout << "s3 <= s4 :" << (s3 <= s4) << endl;

    cout << "s3 >= s4 :" << (s3 >= s4) << endl;

    String s7 = s2 + s3;
    cout << "s7:" << s7 << endl;

    String s8 = s2 + "world";
    cout << "s8:" << s8 << endl;

    String s9 = "nihao" + s2;
    cout << "s9:" << s9 << endl;

    return 0;
}