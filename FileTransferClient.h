//
// Created by 김민우 on 15. 5. 26..
//

#ifndef MESSAGEQUEUETOMULTICAST_FILETRANSFERCLIENT_H
#define MESSAGEQUEUETOMULTICAST_FILETRANSFERCLIENT_H

#include "header.h"

class FileTransferClient {
private:
    std::thread th;
    char ip[IP_SIZE];
    char port[PORT_SIZE];
    char destpath[BUF_SIZE];
    char others[BUF_SIZE]; // for strtok

    // tcp server
    int sd;
    struct sockaddr_in serv_addr;
    char filename[BUF_SIZE];

public:
//    FileTransferClient(const char* ip, const char* port);
    FileTransferClient(char *line);
    ~FileTransferClient();

    void StartThread();
    void StopThread();
    int PasteProcess(char *outfile, int fd1);
};


#endif //MESSAGEQUEUETOMULTICAST_FILETRANSFERCLIENT_H
