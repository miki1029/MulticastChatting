//
// Created by 김민우 on 15. 5. 25..
//

#ifndef MULTICASTCHATTING_MESSAGEQUEUETOMULTICAST_H
#define MULTICASTCHATTING_MESSAGEQUEUETOMULTICAST_H

#include "header.h"

class MessageQueueToMulticast {
private:
    std::thread th;
    char userInfo[USR_SIZE];

    // Message Queue
    struct my_msgbuf buf;
    int msqid;
    key_t key;

    // Multicast
    int send_sock;
    struct sockaddr_in mul_adr;
    int time_live = TTL;
    char multicastBuf[USR_SIZE + BUF_SIZE];

public:
    MessageQueueToMulticast(const char *ip, const char *port, const char *user);
    ~MessageQueueToMulticast();

    void StartThread();
    void StopThread();
    void GetIPAddress();
};


#endif //MULTICASTCHATTING_MESSAGEQUEUETOMULTICAST_H
