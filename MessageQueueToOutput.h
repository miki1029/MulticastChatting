//
// Created by 김민우 on 15. 5. 25..
//

#ifndef MULTICASTCHATTING_MESSAGEQUEUETOOUTPUT_H
#define MULTICASTCHATTING_MESSAGEQUEUETOOUTPUT_H

#include "header.h"

class MessageQueueToOutput {
private:
    std::thread th;

    // message queue
    struct my_msgbuf buf;
    int msqid;
    key_t key;

public:
    MessageQueueToOutput();
    ~MessageQueueToOutput();

    void StartThread();
    void StopThread();
};


#endif //MULTICASTCHATTING_MESSAGEQUEUETOOUTPUT_H
