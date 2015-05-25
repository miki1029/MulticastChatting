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

#define BUF_SIZE 200
#define TTL 64

#endif //MESSAGEQUEUETOMUTLCAST_HEADER_H
