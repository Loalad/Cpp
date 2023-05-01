#include "line.hpp"

#include <iostream>

using std::cout;
using std::endl;

class Line::LineImpl{
    class Point{
        friend std::ostream &operator<<(std::ostream &os, const Point &rhs);
    public:
        Point(int ix = 0, int iy = 0);
        ~Point(){
            cout << "Point析构函数" << endl;
        }
    private:
        int _ix;
        int _iy;
    };

    friend std::ostream &operator<<(std::ostream &os, const Line::LineImpl::Point &rhs);
public:
    LineImpl(int x1, int y1, int x2, int y2)
    :_pt1(x1, y1)
    ,_pt2(x2, y2){
        cout << "LineImpl构造函数" << endl;
    }

    void printLine()const;//类外实现
private:
    Point _pt1;
    Point _pt2;
};

Line::LineImpl::Point::Point(int ix, int iy)
:_ix(ix)
,_iy(iy){
    cout << "Point构造函数" << endl;
}

void Line::LineImpl::printLine()const{
    cout << _pt1 << "-->" << _pt2 << endl;
}

std::ostream &operator<<(std::ostream &os, const Line::LineImpl::Point &rhs){
    os << "(" << rhs._ix
        << "," << rhs._iy
        << ")" ;
    return os;
}

Line::Line(int x1, int y1, int x2, int y2)
:_pimpl(new LineImpl(x1, y1, x2, y2)){
    cout << "Line的构造函数" << endl;
}

void Line::printLine() const{
    _pimpl->printLine();
}
