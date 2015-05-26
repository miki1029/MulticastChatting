//
// Created by 김민우 on 15. 5. 26..
//

#ifndef MESSAGEQUEUETOMULTICAST_MESSAGE_H
#define MESSAGEQUEUETOMULTICAST_MESSAGE_H

#include "header.h"
#include "UserInfo.h"

class MessageInfo {
private:
    char username[USR_SIZE];
    char ip[IP_SIZE];
    char message[BUF_SIZE];
    struct my_msgbuf ipcMessage;

public:
    MessageInfo();
    ~MessageInfo();

    MessageInfo* SetUsername(const char *username);
    MessageInfo* SetIP(const char *ip);
    MessageInfo* SetMessage(const char *message);

    // build user name, message for Multicast
    struct my_msgbuf BuildPacket(long mtype);
    MessageInfo* SetInfoFromPacket(char *packet);

    // build user name, ip, message for Message Passing
    struct my_msgbuf BuildIPCMessage(long mtype);
    UserInfo BuildUserInfo();
};


#endif //MESSAGEQUEUETOMULTICAST_MESSAGE_H
