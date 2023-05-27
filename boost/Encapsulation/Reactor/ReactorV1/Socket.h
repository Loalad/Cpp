//与文件描述符相关的操作，包括fd的创建，关闭，获取
#ifndef __SOCKET_H__
#define __SOCKET_H__

#include "NonCopyable.h"

class Socket: public NonCopyable {
public:
    Socket();
    explicit Socket(int fd);
    ~Socket();
    int fd() const;
    void shutDownWrite();

private:
    int _fd;
};



#endif

