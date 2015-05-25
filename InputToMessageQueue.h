//
// Created by 김민우 on 15. 5. 25..
//

#ifndef MULTICASTCHATTING_INPUTTOMESSAGEQUEUE_H
#define MULTICASTCHATTING_INPUTTOMESSAGEQUEUE_H

#include <iostream>
#include <thread>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define BUF_SIZE 200

class InputToMessageQueue {
private:
    std::thread th;

    // message queue
    struct my_msgbuf {
        long mtype;
        char mtext[BUF_SIZE];
    };
    struct my_msgbuf buf;
    int msqid;
    key_t key;

public:
    InputToMessageQueue();
    ~InputToMessageQueue();

    void StartThread();
    void StopThread();
};


#endif //MULTICASTCHATTING_INPUTTOMESSAGEQUEUE_H
