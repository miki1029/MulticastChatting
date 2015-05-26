//
// Created by 김민우 on 15. 5. 26..
//

#include "FileTransferServer.h"

FileTransferServer::FileTransferServer(const char* username, const char* srcpath,
                                       const char* destpath, const char* port) {
    strcpy(this->username, username);
    strcpy(this->srcpath, srcpath);
    strcpy(this->destpath, destpath);
    strcpy(this->port, port);

    // Server setup
    serverSock = socket(PF_INET, SOCK_STREAM, 0);
    if(serverSock == -1) {
        perror("socket");
        exit(1);
    }
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family=AF_INET;
    serv_addr.sin_addr.s_addr=htonl(INADDR_ANY);
    serv_addr.sin_port=htons(atoi(this->port));
}

FileTransferServer::FileTransferServer(char *line) {
    char *cptr = line;

    cptr = strtok(line, " ");
    cptr += (int)strlen(cptr) + 1;
    strcpy(others, cptr);

    cptr = strtok(others, " ");
    strcpy(username, cptr);
    cptr += (int)strlen(username) + 1;
    strcpy(others, cptr);

    cptr = strtok(others, " ");
    strcpy(srcpath, cptr);
    cptr += (int)strlen(srcpath) + 1;
    strcpy(others, cptr);

    cptr = strtok(others, " ");
    strcpy(destpath, cptr);
    cptr += (int)strlen(destpath) + 1;
    strcpy(port, cptr);

    // Server setup
    serverSock = socket(PF_INET, SOCK_STREAM, 0);
    if(serverSock == -1) {
        perror("socket");
        exit(1);
    }
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family=AF_INET;
    serv_addr.sin_addr.s_addr=htonl(INADDR_ANY);
    serv_addr.sin_port=htons(atoi(port));
}

FileTransferServer::~FileTransferServer() {

}

void FileTransferServer::StartThread() {
    th = std::thread([=]() {
        if( bind(serverSock, (struct sockaddr*) &serv_addr, sizeof(serv_addr)) == -1 ) {
            perror("bind");
            exit(1);
        }
        if( listen(serverSock, 5) == -1 ) {
            perror("listen");
            exit(1);
        }
        clnt_addr_size = sizeof(clnt_addr);
        clientSock = accept(serverSock, (struct sockaddr*)&clnt_addr, (socklen_t *) &clnt_addr_size);
        if(clientSock == -1) {
            perror("accept");
            exit(1);
        }

        // send destpath
        write(clientSock, destpath, strlen(destpath));

        // file transfer
        CopyProcess(srcpath, clientSock);
    });
}

void FileTransferServer::StopThread() {
    close(clientSock);
    th.detach();
}

int FileTransferServer::CopyProcess(char *infile, int fd2) {
    int fd1;
    ssize_t rcount, wcount;
    char buffer[BUFSIZ];
    int errors = 0;
    struct stat statbuf;

    // fd1 : infile open
    if ((fd1 = open(infile, O_RDONLY)) < 0) {
        fprintf(stderr, "%s: cannot open for reading: %s\n", infile, strerror(errno));
        return 1;
    }

    // statbuf : mode
    if (fstat(fd1, &statbuf) < 0) {
        fprintf(stderr, "%s: fstat fail: %s\n", infile, strerror(errno));
        errors++;
    }
    // send mode
    wcount = write(fd2, &statbuf, sizeof(statbuf));
    if (wcount != rcount) {
        fprintf(stderr, "%d: write error: %s\n", fd2, strerror(errno));
        errors++;
    }


    // send data
    while ((rcount = read(fd1, buffer, sizeof(buffer))) > 0) {
        wcount = write(fd2, buffer, rcount);
        if (wcount != rcount) {
            fprintf(stderr, "%d: write error: %s\n", fd2, strerror(errno));
            errors++;
            break;
        }
    }
    if (rcount < 0) {
        fprintf(stderr, "%s: read error: %s\n", infile, strerror(errno));
        errors++;
    }

    // infile close
    if (fd1 != 0) {
        if (close(fd1) < 0) {
            fprintf(stderr, "%s: close error: %s\n", infile, strerror(errno));
            errors++;
        }
    }

    return (errors != 0);
}
