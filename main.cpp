#include <iostream>
#include "MessageQueueToMutlcast.h"
#include "InputToMessageQueue.h"
#include "MessageQueueToOutput.h"
#include "MulticastToMessageQueue.h"

using namespace std;

int main(int argc, char** argv) {
    cout << "hi" << endl;

    InputToMessageQueue input;
//    MessageQueueToMutlcast toMulticast(argv[1], argv[2]);
//    MulticastToMessageQueue fromMulticast(argv[1], argv[2]);
//    MessageQueueToMutlcast toMulticast("224.1.1.2", "20000");
    MulticastToMessageQueue fromMulticast("224.1.1.2", "20000");
    MessageQueueToOutput output;

    input.StartThread();
//    toMulticast.StartThread();
    fromMulticast.StartThread();
    output.StartThread();

    sleep(100);

    input.StopThread();
//    toMulticast.StopThread();
    fromMulticast.StopThread();
    output.StopThread();

    cout << "bye" << endl;

    return 0;
}