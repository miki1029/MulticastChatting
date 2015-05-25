//
// Created by 김민우 on 15. 5. 26..
//

#ifndef MESSAGEQUEUETOMUTLCAST_HEADER_H
#define MESSAGEQUEUETOMUTLCAST_HEADER_H

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <thread>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
//#include <sys/utsname.h>
//#include <netinet/in.h>
//#include <netdb.h>
//#include <net/if.h>
#include <signal.h>

#define BUF_SIZE 200
#define USR_SIZE 100
#define TTL 64

struct my_msgbuf {
    long mtype;
    char mtext[BUF_SIZE];
};

#endif //MESSAGEQUEUETOMUTLCAST_HEADER_H
