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
    if(strchr(argv[3], ':') != NULL) {
        std::cout << "Don't use ':' in user name" << std::endl;
        return 1;
    }

    InputToMessageQueue input;
    MessageQueueToMulticast toMulticast(argv[1], argv[2], argv[3]);
    MulticastToMessageQueue fromMulticast(argv[1], argv[2]);
    MessageQueueToOutput output;

    input.StartThread();
    toMulticast.StartThread();
    fromMulticast.StartThread();
    output.StartThread();

    signal(SIGINT, handler);

    std::cout << std::endl << "Multicast Chatting Program" << std::endl
              << "Enjoy Your Chat !!" << std::endl << std::endl;

    while(runState) { // SIGINT(Ctrl+c) -> break
        sleep(1);
    }

    input.StopThread();
    toMulticast.StopThread();
    fromMulticast.StopThread();
    output.StopThread();

    std::cout << std::endl << "Exit Chatting Program !" << std::endl;

    return 0;
}
