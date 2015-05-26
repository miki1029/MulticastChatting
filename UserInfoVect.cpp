//
// Created by 김민우 on 15. 5. 26..
//

#include "UserInfoVect.h"

UserInfoVect::UserInfoVect() {

}

UserInfoVect::~UserInfoVect() {

}

void UserInfoVect::AddUser(UserInfo ui) {
    userVect.push_back(ui);
}

void UserInfoVect::AddUserIPByName(const char *username, const char *ip) {
    for(UserInfo ui : userVect) {
        if(strcmp(username, ui.GetUsername()) == 0)
            ui.SetIP(ip);
    }
}

const char *UserInfoVect::FindIPByName(const char *username) {
    for(UserInfo ui : userVect) {
        if(strcmp(username, ui.GetUsername()) == 0)
            return ui.GetIP();
    }
    return "0.0.0.0";
}

void UserInfoVect::PrintUsers() {
    for(UserInfo ui : userVect) {
        std::cout << ui.GetUsername() << ":" << ui.GetIP() << std::endl;
    }
}
