#include "TcpServer.h"

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

void test0() {
    TcpServer server("172.28.180.35", 8888);
    server.setAllCallback(std::move(onConnection),
                          std::move(onMessage),
                          std::move(onClose));
    server.start();
}

int main() {
    test0();
    return 0;
}

