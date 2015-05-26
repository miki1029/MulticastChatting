//
// Created by 김민우 on 15. 5. 26..
//

#ifndef MESSAGEQUEUETOMULTICAST_FILETRANSFERSERVER_H
#define MESSAGEQUEUETOMULTICAST_FILETRANSFERSERVER_H

#include "header.h"

class FileTransferServer {
private:
    std::thread th;
    char username[USR_SIZE];
    char srcpath[BUF_SIZE];
    char destpath[BUF_SIZE];
    char port[PORT_SIZE];
    char others[2 * BUF_SIZE]; // for strtok

    // tcp server
    int serverSock;
    int clientSock;
    struct sockaddr_in serv_addr;
    struct sockaddr_in clnt_addr;
    char filepath[BUF_SIZE];
    int clnt_addr_size;

public:
    FileTransferServer(const char* username, const char* srcpath,
                       const char* destpath, const char* port);
    FileTransferServer(char* line);
    ~FileTransferServer();

    void StartThread();
    void StopThread();
    int CopyProcess(char *infile, int fd2);
};


#endif //MESSAGEQUEUETOMULTICAST_FILETRANSFERSERVER_H
