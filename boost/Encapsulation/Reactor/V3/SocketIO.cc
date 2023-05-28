#include "SocketIO.h"

#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>

SocketIO::SocketIO(int fd): _fd(fd) {}

SocketIO::~SocketIO() {
    close(_fd);
}

int SocketIO::readn(char *buf, int len) {
    int left = len;
    char *pstr = buf;
    int ret = 0;

    while(left > 0) {
        ret = read(_fd, pstr, left);
        if(ret == -1 && errno == EINTR) {
            continue;
        }
        else if(ret == -1) {
            perror("read error -1");
            return len - ret;
        }
        else if(ret == 0) {
            break;
        }
        else {
            pstr += ret;
            left -= ret;
        }
    }
    return len - left;
}
     
int SocketIO::writen(const char *buf, int len) {
    int left = len;
    const char *pstr = buf;
    int ret = 0;
    
    while(left > 0) {
        ret = write(_fd, pstr, left);
        if(ret == -1 && errno == EINTR) {
            continue;
        }
        else if(ret == -1) {
            perror("writen error -1");
            return len - left;
        }
        else if(ret == 0) {
            break;
        }
        else {
            pstr += ret;
            left -= ret;
        }
    }
    return len - left;
}
     
int SocketIO::readLine(char *buf, int len) {
    int left = len - 1;
    char *pstr = buf;
    int ret = 0;
    int total = 0;

    while(left > 0) {
        //MSG_PEEK不会将缓冲区中的数据进行清空，只会进行拷贝操作
        ret = recv(_fd, pstr, left, MSG_PEEK);
        if(ret == -1 && errno == EINTR) {
            continue;
        }
        else if(ret == -1) {
            perror("readLine error -1");
            return len - left;
        }
        else if(ret == 0) {
            break;
        }
        else {
            for(int idx = 0; idx < ret; ++idx) {
                if(pstr[idx] == '\n') {
                    int sz = idx + 1;
                    readn(pstr, sz);
                    pstr += sz;
                    *pstr = '\0';

                    return total + sz;
                }
            }

            readn(pstr, ret);//从内核态拷贝到用户态
            total += ret;
            pstr += ret;
            left -= ret;
        }
    }
    *pstr = '\0';

    return total - left;
}
