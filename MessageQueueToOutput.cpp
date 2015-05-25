//
// Created by 김민우 on 15. 5. 25..
//

#include "MessageQueueToOutput.h"

MessageQueueToOutput::MessageQueueToOutput() {
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
    buf.mtype = 2;
}

MessageQueueToOutput::~MessageQueueToOutput() {

}

void MessageQueueToOutput::StartThread() {
    th = std::thread([=]() {
        while(true) {
            if (msgrcv(msqid, &buf, sizeof(buf.mtext), 0, 0) == -1) {
                perror("msgrcv");
                exit(1);
            }
            std::cout << std::endl << "read message : " << buf.mtext << std::endl;
        }
    });
}
void MessageQueueToOutput::StopThread() {
    th.detach();
}
