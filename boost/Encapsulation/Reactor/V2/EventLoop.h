#ifndef __EVENTLOOP_H__
#define __EVENTLOOP_H__

#include "Acceptor.h"
#include "TcpConnection.h"

#include <vector>
#include <map>
#include <memory>
#include <functional>

using std::vector;
using std::map;
using std::shared_ptr;
using std::function;

using TcpConnectionPtr = shared_ptr<TcpConnection>;
using TcpConnectionCallback = function<void (const TcpConnectionPtr &)>;

class EventLoop {
public:
    EventLoop(Acceptor &);
    ~EventLoop();

    int createEpollFd();
    void addEpollReadFd(int fd);
    void delEpollReadFd(int fd);
    void loop();
    void unloop();
    void waitEpollFd();

    void setConnectionCallback(TcpConnectionCallback &&);
    void setMessageCallback(TcpConnectionCallback &&);
    void setCloseCallback(TcpConnectionCallback &&);
    void handleNewConnection();
    void handleMessage(int fd);

private:
    int _epfd;
    bool _isLooping;
    Acceptor &_acceptor;
    vector<struct epoll_event> _evtList;
    map<int, shared_ptr<TcpConnection>> _conns;
    TcpConnectionCallback _onConnectionCb;//建立连接
    TcpConnectionCallback _onMessageCb;//消息到达
    TcpConnectionCallback _onCloseCb;//断开连接
};


#endif
