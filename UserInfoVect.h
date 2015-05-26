//
// Created by 김민우 on 15. 5. 26..
//

#ifndef MESSAGEQUEUETOMULTICAST_USERINFOVECT_H
#define MESSAGEQUEUETOMULTICAST_USERINFOVECT_H

#include "header.h"
#include "UserInfo.h"

class UserInfoVect {
private:
    std::vector<UserInfo> userVect;
public:
    UserInfoVect();
    ~UserInfoVect();
    void AddUser(UserInfo ui);
    void AddUserIPByName(const char *username, const char *ip);
    const char* FindIPByName(const char* username);
};

extern UserInfoVect userInfoVect;

#endif //MESSAGEQUEUETOMULTICAST_USERINFOVECT_H
