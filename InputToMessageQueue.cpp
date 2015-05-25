//
// Created by 김민우 on 15. 5. 25..
//

#include "InputToMessageQueue.h"

InputToMessageQueue::InputToMessageQueue() {
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
}

InputToMessageQueue::~InputToMessageQueue() {
    // clear Message Queue
    if(msgctl(msqid, IPC_RMID, NULL) == -1) {
        perror("msgctl");
        exit(1);
    }
}

void InputToMessageQueue::StartThread() {
    th = std::thread([=]() {
        // buf.mtext : read message from keyboard
        // std::cout << "write message : ";
        while(fgets(buf.mtext, sizeof(buf.mtext), stdin) != NULL) {
            size_t len = strlen(buf.mtext);

            // ditch newline at end, if it exists
            if(buf.mtext[len-1] == '\n') buf.mtext[len-1] = '\0';

            // std::cout << "Input->MQ(1) : " << buf.mtext << std::endl;
            // write message to Message Queue (+1 for '\0')
            if(msgsnd(msqid, &buf, len+1, 0) == -1)
                perror("msgsnd");

            // std::cout << "write message : ";
        }
    });
}

void InputToMessageQueue::StopThread() {
    th.detach();
}

