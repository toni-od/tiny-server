#include "header.h"

int ts_serve(char *ip, int port, int backlog) {   
    struct sockaddr_in servaddr;
    int ssock, csock;

    ssock = ts_listen(ip, port, backlog);
    if(ssock < 0) {
        perror("listen() error...");
        return -1;
    }

    while(1) {
        csock = ts_accept(ssock);
        if(!csock) {
            perror("accept() error...");
            continue;
        }
        
        if(!fork()) {
            ts_handle(ssock, csock);
        }
    }

    return 0;
}
