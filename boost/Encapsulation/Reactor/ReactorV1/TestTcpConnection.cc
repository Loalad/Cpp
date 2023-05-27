#include <iostream>

#include "Acceptor.h"
#include "TcpConnection.h"


using std::cout;
using std::endl;

void test0() {
    Acceptor acceptor("172.28.180.35", 8888);
    acceptor.ready();

    TcpConnection con(acceptor.accept());

    cout << con.toString() << " has connectd" << endl;

    while(1) {
        cout << ">>recv msg from client: " << con.receive() << endl;
        con.send("hello baby\n");
    }
}

int main() {
    test0();
    return 0;
}

