//
// Created by 김민우 on 15. 5. 25..
//

#ifndef MULTICASTCHATTING_MULTICASTTOMESSAGEQUEUE_H
#define MULTICASTCHATTING_MULTICASTTOMESSAGEQUEUE_H

#include "header.h"

class MulticastToMessageQueue {
private:
    std::thread th;

    // Message Queue
    struct my_msgbuf buf;
    int msqid;
    key_t key;

    // Multicast
    int recv_sock;
    int str_len;
    struct sockaddr_in adr;
    struct ip_mreq join_adr;

public:
    MulticastToMessageQueue(const char *ip, const char *port);
    ~MulticastToMessageQueue();

    void StartThread();
    void StopThread();
};


#endif //MULTICASTCHATTING_MULTICASTTOMESSAGEQUEUE_H
