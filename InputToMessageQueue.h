//
// Created by 김민우 on 15. 5. 25..
//

#ifndef MULTICASTCHATTING_INPUTTOMESSAGEQUEUE_H
#define MULTICASTCHATTING_INPUTTOMESSAGEQUEUE_H

#include "header.h"
#include "FileTransferServer.h"
#include "FileTransferClient.h"

class InputToMessageQueue {
private:
    std::thread th;
    FileTransferServer *fts;
    FileTransferClient *ftc;

    // message queue
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
