//
// Created by 김민우 on 15. 5. 26..
//

#include "UserInfo.h"

UserInfo::UserInfo() {

}

UserInfo::UserInfo(const char *username, const char *ip) {
    this->SetUsername(username)->SetIP(ip);
}

UserInfo::~UserInfo() {

}

UserInfo* UserInfo::SetUsername(const char *username) {
    strcpy(this->username, username);
    return this;
}

UserInfo* UserInfo::SetIP(const char *ip) {
    strcpy(this->ip, ip);
    return this;
}

const char *UserInfo::GetUsername() {
    return username;
}

const char *UserInfo::GetIP() {
    return ip;
}
