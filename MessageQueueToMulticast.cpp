//
// Created by 김민우 on 15. 5. 25..
//

#include "MessageQueueToMulticast.h"

MessageQueueToMulticast::MessageQueueToMulticast(const char *ip, const char *port, const char *user) {
    // init Message Queue
    // key : ipc key from "chatkey" file
    if((key = ftok("chatkey", 'B')) == -1) {
        perror("ftok");
        exit(1);
    }

    // msqid : create and get message queue
    if((msqid = msgget(key, 0644 | IPC_CREAT)) == -1) {
        perror("msgget");
        exit(1);
    }

    // mtype : 1(input->MQ->Multicast), 2(Multicast->MQ->output)
    buf.mtype = 1;


    // init Mutlciast
    send_sock = socket(PF_INET, SOCK_DGRAM, 0);
    memset(&mul_adr, 0, sizeof(mul_adr));
    mul_adr.sin_family = AF_INET;
    mul_adr.sin_addr.s_addr = inet_addr(ip);
    mul_adr.sin_port = htons(atoi(port));
    setsockopt(send_sock, IPPROTO_IP, IP_MULTICAST_TTL, (void*)&time_live, sizeof(time_live));

    // init userInfo
    strcpy(userInfo, user);
//    sprintf(userInfo, "%s", user);
//    struct sockaddr_in localAddr;
//    localAddr.sin_addr.s_addr = htonl(INADDR_ANY);
//    char* userIP = inet_ntoa(localAddr.sin_addr);
//    std::cout << user << "(" << userIP << ") : " << std::endl;
}

MessageQueueToMulticast::~MessageQueueToMulticast() {
    close(send_sock);
}

void MessageQueueToMulticast::StartThread() {
    // thread create
    th = std::thread([=]() {
        while(true) {
            // read Message Queue
            if (msgrcv(msqid, &buf, sizeof(buf.mtext), 0, 0) == -1) {
                perror("msgrcv");
                exit(1);
            }
            // add User Info
            sprintf(multicastBuf, "%s : %s", userInfo, buf.mtext);
            // send Multicast
            sendto(send_sock, multicastBuf, strlen(multicastBuf), 0, (struct sockaddr*)&mul_adr, sizeof(mul_adr));
            // std::cout << std::endl << "MQ(1)->Multicast : " << multicastBuf << std::endl;
        }
    });
}

void MessageQueueToMulticast::StopThread() {
    th.detach();
}