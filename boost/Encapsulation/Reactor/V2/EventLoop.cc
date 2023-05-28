#include "EventLoop.h"

#include <unistd.h>
#include <sys/epoll.h>
#include <errno.h>
#include <iostream>

EventLoop::EventLoop(Acceptor &acceptor)
: _epfd(createEpollFd())
, _isLooping(false)
, _acceptor(acceptor)
, _evtList(1024) {
    addEpollReadFd(_acceptor.fd());
}


EventLoop::~EventLoop() {
    close(_epfd);
}

int EventLoop::createEpollFd() {
    int fd =  epoll_create1(0);
    if(-1 == fd) {
        perror("createEpollFd");
        return -1;
    }
    return fd;
}

void EventLoop::addEpollReadFd(int fd) {
    struct epoll_event evt;
    evt.data.fd = fd;
    evt.events = EPOLLIN;
    int ret = epoll_ctl(_epfd, EPOLL_CTL_ADD, fd, &evt);
    if(-1 == ret) {
        perror("epoll_ctl_add");
        return;
    }
    return;
}
void EventLoop::delEpollReadFd(int fd) {
    struct epoll_event evt;
    evt.events = EPOLLIN;
    evt.data.fd = fd;

    int ret = epoll_ctl(_epfd, EPOLL_CTL_DEL, fd, &evt);
    if(-1 == ret) {
        perror("epoll_ctl_del");
        return;
    }
    return;
}

void EventLoop::loop() {
    _isLooping = true;
    while(_isLooping) {
        waitEpollFd();
    }
}

void EventLoop::unloop() {
    _isLooping = false;
}

void EventLoop::waitEpollFd() {
    int nready;
    do{
        nready = epoll_wait(_epfd, &*_evtList.begin(), _evtList.size(), 3000);
    } while(-1 == nready && errno == EINTR);

    if(-1 == nready) {
        perror("epoll_wait");
        return;
    }
    else if(0 == nready) {
        std::cout << ">>epoll_timeout" << std::endl;
    }
    else {
        if(nready == static_cast<int>(_evtList.size())) {
            _evtList.resize(2 * _evtList.size());
        }
        for(int idx = 0; idx < nready; ++idx) {
            int fd = _evtList[idx].data.fd;
            if(fd == _acceptor.fd()) {
                handleNewConnection();
            }
            else {
                handleMessage(fd);
            }
        }
    }
}

void EventLoop::setConnectionCallback(TcpConnectionCallback &&cb) {
    _onConnectionCb = std::move(cb);
}

void EventLoop::setMessageCallback(TcpConnectionCallback &&cb) {
    _onMessageCb = std::move(cb);
}

void EventLoop::setCloseCallback(TcpConnectionCallback &&cb) {
    _onCloseCb = std::move(cb);
}

void EventLoop::handleNewConnection() {
   int connfd = _acceptor.accept();
   if(-1 == connfd) {
       perror("accept");
       return;
   }

   addEpollReadFd(connfd);

   TcpConnectionPtr con(new TcpConnection(connfd));

   con->setConnectionCallback(_onConnectionCb);
   con->setMessageCallback(_onMessageCb);
   con->setCloseCallback(_onCloseCb);

   _conns.insert(make_pair(connfd, con));

   con->handleConnectionCallback();
}

//收到的消息有两种情况
//1、对方断开连接，readn的返回值为0
//2、对方发来数据，readn的返回值大于0
void EventLoop::handleMessage(int fd) {
    auto it = _conns.find(fd);
    if(it != _conns.end()) {
        bool flag = it->second->isClosed();
        if(flag) {
            //断开连接
            it->second->handleCloseCallback();
            delEpollReadFd(fd);
            _conns.erase(it);
        }
        else {
            //进行数据收发
            it->second->handleMessageCallback();
        }
    }
    else {
        std::cout << "该连接不存在" << std::endl;
        return;
    }
}
