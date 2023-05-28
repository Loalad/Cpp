#include "TcpConnection.h"
#include <sstream>

using std::ostringstream;

TcpConnection::TcpConnection(int fd)
: _sockIO(fd)
, _sock(fd)
, _localAddr(getLocalAddr())
, _peerAddr(getPeerAddr()) {}


TcpConnection::~TcpConnection() {}

void TcpConnection::send(const string &msg) {
    _sockIO.writen(msg.c_str(), msg.size());
}

string TcpConnection::receive() {
    char buf[65535] = {0};
    _sockIO.readLine(buf, sizeof(buf));

    return string(buf);
}

string TcpConnection::toString() {
    ostringstream oss;
    oss << _localAddr.ip() << ":"
        << _localAddr.port() << "----->"
        << _peerAddr.ip() << ":"
        << _peerAddr.port();

    return oss.str();
}

bool TcpConnection::isClosed() const {
    char buf[10] = {0};
    int ret = ::recv(_sock.fd(), buf, sizeof(buf), MSG_PEEK);
    return 0 == ret;
}

//获取本端的网络地址信息
InetAddress TcpConnection::getLocalAddr()
{
    struct sockaddr_in addr;
    socklen_t len = sizeof(struct sockaddr );
    //获取本端地址的函数getsockname
    int ret = getsockname(_sock.fd(), (struct sockaddr *)&addr, &len);
    if(-1 == ret)
    {
        perror("getsockname");
    }

    return InetAddress(addr);
}

//获取对端的网络地址信息
InetAddress TcpConnection::getPeerAddr()
{
    struct sockaddr_in addr;
    socklen_t len = sizeof(struct sockaddr );
    //获取对端地址的函数getpeername
    int ret = getpeername(_sock.fd(), (struct sockaddr *)&addr, &len);
    if(-1 == ret)
    {
        perror("getpeername");
    }

    return InetAddress(addr);
}

//注册TCP连接三个事件
void TcpConnection::setConnectionCallback(const TcpConnectionCallback &cb) {
    _onConnectionCb = cb;
}

void TcpConnection::setMessageCallback(const TcpConnectionCallback &cb) {
    _onMessageCb = cb;
}

void TcpConnection::setCloseCallback(const TcpConnectionCallback &cb) {
    _onCloseCb = cb;
}

//执行TCP三个事件
//回调函数有一个参数TcpConnectionPtr(即TcpConnection的智能指针)
void TcpConnection::handleConnectionCallback() {
    if(_onConnectionCb) {
        _onConnectionCb(shared_from_this());
    }
}

void TcpConnection::handleMessageCallback() {
    if(_onMessageCb) {
        _onMessageCb(shared_from_this());
    }
}

void TcpConnection::handleCloseCallback() {
    if(_onCloseCb) {
        _onCloseCb(shared_from_this());
    }
}
