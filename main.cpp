#include <iostream>
#include "MessageQueueToMulticast.h"
#include "InputToMessageQueue.h"
#include "MessageQueueToOutput.h"
#include "MulticastToMessageQueue.h"
#include "UserInfoVect.h"

bool runState = true;
UserInfoVect userInfoVect;

void handler(int signum) {
    runState = false;
}

int main(int argc, char** argv) {
    if(argc != 4) {
        std::cout << "Usage : " << argv[0] << " <GroupIP> <PORT> <User Name>\n" << std::endl;
        return 1;
    }
    if(strchr(argv[3], '\t') != NULL) {
        std::cout << "Don't use ':' in user name" << std::endl;
        return 1;
    }

    InputToMessageQueue input;
    MessageQueueToMulticast toMulticast(argv[1], argv[2], argv[3]);
    MulticastToMessageQueue fromMulticast(argv[1], argv[2]);
//    MessageQueueToMulticast toMulticast("224.1.1.2", "20000", argv[1]);
//    MulticastToMessageQueue fromMulticast("224.1.1.2", "20000");
    MessageQueueToOutput output;

    input.StartThread();
    toMulticast.StartThread();
    fromMulticast.StartThread();
    output.StartThread();

    while(runState) {
        sleep(1);
        signal(SIGINT, handler);
    }

    input.StopThread();
    toMulticast.StopThread();
    fromMulticast.StopThread();
    output.StopThread();

    std::cout << "Exit Chatting Program !" << std::endl;

    return 0;
}
