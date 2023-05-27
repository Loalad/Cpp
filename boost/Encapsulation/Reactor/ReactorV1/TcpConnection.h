#ifndef __TCPCONNECTION_H__
#define __TCPCONNECTION_H__

#include "SocketIO.h"
#include "InetAddress.h"
#include "Socket.h"

#include <string>
using std::string;

class TcpConnection {
public:
    explicit TcpConnection(int fd);
    ~TcpConnection();
    void send(const string &msg);
    string receive();

    string toString();

private:
    //获取本段地址和对端地址
    InetAddress getLocalAddr();
    InetAddress getPeerAddr();

private:
    SocketIO _sockIO;
    Socket _sock;//调试
    InetAddress _localAddr;
    InetAddress _peerAddr;
};


#endif

