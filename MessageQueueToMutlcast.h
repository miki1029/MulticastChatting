//
// Created by 김민우 on 15. 5. 25..
//

#ifndef MULTICASTCHATTING_MESSAGEQUEUETOMULTICAST_H
#define MULTICASTCHATTING_MESSAGEQUEUETOMULTICAST_H

#include "header.h"

class MessageQueueToMutlcast {
private:
    std::thread th;

    // Message Queue
    struct my_msgbuf {
        long mtype;
        char mtext[200];
    };
    struct my_msgbuf buf;
    int msqid;
    key_t key;

    // Multicast
    int send_sock;
    struct sockaddr_in mul_adr;
    int time_live = TTL;

public:
    MessageQueueToMutlcast(const char *ip, const char *port);
    ~MessageQueueToMutlcast();

    void StartThread();
    void StopThread();
};


#endif //MULTICASTCHATTING_MESSAGEQUEUETOMULTICAST_H
