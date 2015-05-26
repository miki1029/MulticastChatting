//
// Created by 김민우 on 15. 5. 26..
//

#include "FileTransferServer.h"

//FileTransferServer::FileTransferServer(const char* username, const char* srcpath,
//                                       const char* destpath, const char* port) {
//    strcpy(this->username, username);
//    strcpy(this->srcpath, srcpath);
//    strcpy(this->destpath, destpath);
//    strcpy(this->port, port);
//
//    // Server setup
//    serv_sd = socket(PF_INET, SOCK_STREAM, 0);
//    if(serv_sd == -1) {
//        perror("socket");
//        exit(1);
//    }
//    memset(&serv_addr, 0, sizeof(serv_addr));
//    serv_addr.sin_family=AF_INET;
//    serv_addr.sin_addr.s_addr=htonl(INADDR_ANY);
//    serv_addr.sin_port=htons(atoi(this->port));
//}

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

    std::cout << username << "," << srcpath << "," << destpath << "," << port << std::endl;
}

FileTransferServer::~FileTransferServer() {

}

void FileTransferServer::StartThread() {
    th = std::thread([=]() {
        serv_sd = socket(PF_INET, SOCK_STREAM, 0);
        if(serv_sd == -1) {
            perror("socket");
            exit(1);
        }
        memset(&serv_addr, 0, sizeof(serv_addr));
        serv_addr.sin_family=AF_INET;
        serv_addr.sin_addr.s_addr=htonl(INADDR_ANY);
        serv_addr.sin_port=htons(atoi(port));

        std::cout << "bind..." << std::endl;
        if( bind(serv_sd, (struct sockaddr*) &serv_addr, sizeof(serv_addr)) == -1 ) {
            perror("bind");
            exit(1);
        }
        std::cout << "listen..." << std::endl;
        if( listen(serv_sd, 5) == -1 ) {
            perror("listen");
            exit(1);
        }
        std::cout << "accept..." << std::endl;
        clnt_addr_size = sizeof(clnt_addr);
        clnt_sd = accept(serv_sd, (struct sockaddr*)&clnt_addr, &clnt_addr_size);
        if(clnt_sd == -1) {
            perror("accept");
            exit(1);
        }

        std::cout << "ok..." << std::endl;
        // send destpath
        std::cout << "send destpath : [" << destpath << "]" << std::endl;
        write(clnt_sd, destpath, strlen(destpath));

        // file transfer
        CopyProcess(srcpath, clnt_sd);
    });
    StopThread();
}

void FileTransferServer::StopThread() {
    close(clnt_sd);
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
    std::cout << "send mode : [" << statbuf.st_mode << "]" << std::endl;
    wcount = write(fd2, &statbuf, sizeof(statbuf));
    if (wcount != rcount) {
        fprintf(stderr, "%d: write error: %s\n", fd2, strerror(errno));
        errors++;
    }


    // send data
    while ((rcount = read(fd1, buffer, sizeof(buffer))) > 0) {
        wcount = write(fd2, buffer, rcount);
        if (wcount != rcount) {
            fprintf(stderr, "<%d: write error: %s>\n", fd2, strerror(errno));
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
