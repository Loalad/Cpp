#ifndef __TCPCONNECTION_H__
#define __TCPCONNECTION_H__

#include "SocketIO.h"
#include "InetAddress.h"
#include "Socket.h"

#include <string>
#include <memory>
#include <functional>
using std::string;
using std::function;
using std::shared_ptr;

class TcpConnection: public std::enable_shared_from_this<TcpConnection> {
    using TcpConnectionPtr = shared_ptr<TcpConnection>;
    using TcpConnectionCallback = function<void (const TcpConnectionPtr &)>;
public:
    explicit TcpConnection(int fd);
    ~TcpConnection();
    void send(const string &msg);
    string receive();

    string toString();

    bool isClosed() const;

    //注册TCP连接三个事件
    void setConnectionCallback(const TcpConnectionCallback &);
    void setMessageCallback(const TcpConnectionCallback &);
    void setCloseCallback(const TcpConnectionCallback &);

    //执行TCP三个事件
    void handleConnectionCallback();
    void handleMessageCallback();
    void handleCloseCallback();

private:
    //获取本段地址和对端地址
    InetAddress getLocalAddr();
    InetAddress getPeerAddr();

private:
    SocketIO _sockIO;
    Socket _sock;//调试
    InetAddress _localAddr;
    InetAddress _peerAddr;

    TcpConnectionCallback _onConnectionCb;//建立连接
    TcpConnectionCallback _onMessageCb;//消息到达
    TcpConnectionCallback _onCloseCb;//断开连接
};


#endif

