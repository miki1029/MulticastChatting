//
// Created by 김민우 on 15. 5. 25..
//

#include "MulticastToMessageQueue.h"

MulticastToMessageQueue::MulticastToMessageQueue(const char *ip, const char *port) {
    // init MessageQueue
    // key : ipc key from "chatkey" file
    if((key = ftok("chatkey", 'C')) == -1) {
        perror("ftok");
        exit(1);
    }

    // msqid : create and get message queue
    if((msqid = msgget(key, 0644 | IPC_CREAT)) == -1) {
        perror("msgget");
        exit(1);
    }
    // mtype : 1(input->MQ->Multicast), 2(Multicast->MQ->output)
    buf.mtype = 2;

    // init Multicast
    recv_sock=socket(PF_INET, SOCK_DGRAM, 0);
    memset(&adr, 0, sizeof(adr));
    adr.sin_family=AF_INET;
    adr.sin_addr.s_addr=htonl(INADDR_ANY);
    adr.sin_port=htons(atoi(port));

    std::cout << "bind start" << std::endl;
    if(bind(recv_sock, (struct sockaddr*) &adr, sizeof(adr)) == -1) {
        perror("bind");
        exit(1);
    }
    std::cout << "bind end" << std::endl;

    join_adr.imr_multiaddr.s_addr=inet_addr(ip);
    join_adr.imr_interface.s_addr=htonl(INADDR_ANY);

    setsockopt(recv_sock, IPPROTO_IP,
               IP_ADD_MEMBERSHIP, (void*)&join_adr, sizeof(join_adr));

}

MulticastToMessageQueue::~MulticastToMessageQueue() {
    // clear Message Queue
    if(msgctl(msqid, IPC_RMID, NULL) == -1) {
        perror("msgctl");
        exit(1);
    }
    // close Multicast
    close(recv_sock);
}

void MulticastToMessageQueue::StartThread() {
    th = std::thread([=]() {
        while(true) {
            // read message from Multicast
            str_len = recvfrom(recv_sock, buf.mtext, BUF_SIZE-1, 0, NULL, 0);
            if(str_len<0)
                break;
            buf.mtext[str_len]='\0';

            // ditch newline at end, if it exists
            if(buf.mtext[str_len-1] == '\n') buf.mtext[str_len-1] = '\0';

            std::cout << "Multicast->MQ(2) : " << buf.mtext << std::endl;
            // write message to Message Queue (+1 for '\0')
            if(msgsnd(msqid, &buf, str_len+1, 0) == -1)
                perror("msgsnd");
        }
    });
}

void MulticastToMessageQueue::StopThread() {
    th.detach();
}
