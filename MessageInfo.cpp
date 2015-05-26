//
// Created by 김민우 on 15. 5. 26..
//

#include "MessageInfo.h"

MessageInfo::MessageInfo() {

}

MessageInfo::~MessageInfo() {

}

MessageInfo* MessageInfo::SetUsername(const char *username) {
    strcpy(this->username, username);
    return this;
}

MessageInfo* MessageInfo::SetIP(const char *ip) {
    strcpy(this->ip, ip);
    return this;
}

MessageInfo* MessageInfo::SetMessage(const char *message) {
    strcpy(this->message, message);
    return this;
}

struct my_msgbuf MessageInfo::BuildPacket(long mtype) {
    ipcMessage.mtype = mtype;
    sprintf(ipcMessage.mtext, "%s:%s", username, message);
    return ipcMessage;
}

MessageInfo* MessageInfo::SetInfoFromPacket(char *packet) {
    char *cptr = packet;
    cptr = strtok(packet, ":");
    strcpy(username, cptr);
    cptr += (int)strlen(username) + 1;
    strcpy(message, cptr);

    return this;
}

struct my_msgbuf MessageInfo::BuildIPCMessage(long mtype) {
    ipcMessage.mtype = mtype;
    sprintf(ipcMessage.mtext, "%s(%s) : %s", username, ip, message);
    return ipcMessage;
}

UserInfo MessageInfo::BuildUserInfo() {
    UserInfo ui(username, ip);
    return ui;
}
