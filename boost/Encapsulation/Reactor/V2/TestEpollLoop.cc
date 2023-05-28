#include "TcpConnection.h"
#include "Acceptor.h"
#include "EventLoop.h"

#include <iostream>

using std::cout;
using std::endl;

void onConnection(const TcpConnectionPtr &con) {
    cout << con->toString() << " has connected!!!" << endl;
}

void onMessage(const TcpConnectionPtr &con) {
    string msg = con->receive();
    cout << ">>receive from client:" << msg << endl;
    con->send(msg);
}

void onClose(const TcpConnectionPtr &con) {
    cout << con->toString() << " has closed!!!" << endl;
}

int main() {
    Acceptor acceptor("172.28.180.35", 8888);
    acceptor.ready();

    EventLoop loop(acceptor);
    loop.setConnectionCallback(std::move(onConnection));
    loop.setMessageCallback(std::move(onMessage));
    loop.setCloseCallback(std::move(onClose));

    loop.loop();

    return 0;
}
