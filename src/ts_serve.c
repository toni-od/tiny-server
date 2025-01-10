/* ts_serve.c */

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
        
        int pid = fork();
        if (pid == 0) {
            printf("[new connection] Initializing client process...\n");
            ts_handle(csock);
            exit(0);  // terminate the child process
        } else if (pid > 0) { // not a new process
            close(csock);
        } else {
            perror("fork() error");
        }
    }

    return 0;
}
