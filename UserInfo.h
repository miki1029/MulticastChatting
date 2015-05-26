//
// Created by 김민우 on 15. 5. 26..
//

#ifndef MESSAGEQUEUETOMULTICAST_USERINFO_H
#define MESSAGEQUEUETOMULTICAST_USERINFO_H

#include "header.h"

class UserInfo {
private:
    char username[USR_SIZE];
    char ip[IP_SIZE];

public:
    UserInfo();
    UserInfo(const char *username, const char *ip);
    ~UserInfo();

    UserInfo* SetUsername(const char *username);
    UserInfo* SetIP(const char *ip);

    const char* GetUsername();
    const char* GetIP();
};


#endif //MESSAGEQUEUETOMULTICAST_USERINFO_H
