#include "header.h"
/*
* listen/3
*
* input:
*   ip - the ip address of the server as a string
*   port - the port to listen to
*   backlog - the number of clients the server can
*       accept at a go
*
* output:
*   ssock - a listening tcp socket
*
*/
int ts_listen(char *ip, int port, int backlog) {
    struct sockaddr_in servaddr;
    int ssock;
    
    if(!ip) {
        ip = "127.0.0.0.1";
    }
    if(port == 0) {
        port = 9000;
    }
    if(backlog == 0) {
        backlog = 10;
    }
    
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(port);
    servaddr.sin_addr.s_addr = inet_addr(ip);

    ssock = socket(AF_INET, SOCK_STREAM, 0);
    if(ssock < 0) {
        perror("socket() error...");
        return -1;
    }

    if(bind(ssock, (struct sockaddr *)&servaddr, sizeof(struct sockaddr)) == -1) {
        perror("bind() error...");
        return -1;
    }

    if(listen(ssock, backlog) == -1) {
        perror("listen error...");
        return -1;
    }
    printf("Server is listening on port %d\n", port);
    
    return ssock;
}