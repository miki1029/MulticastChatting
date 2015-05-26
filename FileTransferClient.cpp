//
// Created by 김민우 on 15. 5. 26..
//

#include "FileTransferClient.h"
#include "UserInfoVect.h"

FileTransferClient::FileTransferClient(char *line) {
    char *cptr = line;

    cptr = strtok(line, " ");
    cptr += (int)strlen(cptr) + 1;
    strcpy(others, cptr);

    cptr = strtok(others, " ");
    strcpy(username, cptr);
    cptr += (int)strlen(username) + 1;
    strcpy(port, cptr);

    const char *findIP = userInfoVect.FindIPByName(username);
    strcpy(ip, findIP);
}

FileTransferClient::~FileTransferClient() {

}

void FileTransferClient::StartThread() {
    th = std::thread([=]() {
        sd=socket(PF_INET, SOCK_STREAM, 0);
        if(sd == -1) {
            perror("socket");
            exit(1);
        }
        memset(&serv_addr, 0, sizeof(serv_addr));
        serv_addr.sin_family=AF_INET;
        serv_addr.sin_addr.s_addr=inet_addr(ip);
        serv_addr.sin_port=htons(atoi(port));
        if( connect(sd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1 ){
            perror("connect");
            exit(1);
        }

        // input filepath
        read(sd, destpath, sizeof(destpath));
        write(sd, "ok", 2);

        // file transfer
        PasteProcess(destpath, sd);
        std::cout << "file transfer complete !" << std::endl;
    });
    StopThread();
}

void FileTransferClient::StopThread() {
    close(sd);
    th.detach();
}

int FileTransferClient::PasteProcess(char *outfile, int fd1) {
    int fd2;
    ssize_t rcount, wcount;
    char buffer[BUF_SIZE];
    int errors = 0;
    struct stat statbuf;
    mode_t inmode = 0644;

    // outfile open
    if ((fd2 = open(outfile, O_WRONLY | O_CREAT)) < 0) {
        fprintf(stderr, "%s: cannot open for writing: %s\n", outfile, strerror(errno));
        return 1;
    }

    // set mode
    statbuf.st_mode = inmode;
    if (fchmod(fd2, statbuf.st_mode) < 0) {
        fprintf(stderr, "%s: fchmod fail: %s\n", outfile, strerror(errno));
        errors++;
    }

    // receive data
    while ((rcount = read(fd1, buffer, sizeof(buffer))) > 0) {
        wcount = write(fd2, buffer, rcount);
        if (wcount != rcount) {
            fprintf(stderr, "%s: write error: %s\n", outfile, strerror(errno));
            errors++;
            break;
        }
        if (rcount < BUF_SIZE || rcount == 0) break;
    }
    if (rcount < 0) {
        fprintf(stderr, "%d: read error: %s\n", fd1, strerror(errno));
        errors++;
    }

    // outfile close
    if (fd2 != 0) {
        if (close(fd2) < 0) {
            fprintf(stderr, "%s: close error: %s\n", outfile, strerror(errno));
            errors++;
        }
    }

    return (errors != 0);
}