#ifndef __LINE_HPP__
#define __LINE_HPP__

/*
**PIMPL设计模式好处
**1、实现了信息隐藏
**2、将头文件和动态库将给第三方使用，当实现文件有了变化（升级）时
**   只要头文件不变，第三方只需要替换动态库就可以了（即完成库的平滑升级）
**3、编译防火墙
*/
class Line{
public:
    Line(int x1, int y1, int x2, int y2);
    void printLine()const;

    class LineImpl;
private:
    LineImpl *_pimpl;
};

#endif