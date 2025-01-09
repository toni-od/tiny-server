#include "header.h"

int main(int argc, char *argv[]) {
    struct sockaddr_in servaddr;
    int ssock, csock;
    int port = 9000;
    int backlog = 10;
    char *ip = "0.0.0.0"; // listen on all interfaces
    char buf[1024];
    int ret;
    int pid; // process id representing the process created to handle client communication process

    if(argc == 1) {
        ; // use the defaults
    } else if(argc == 2) {
        port = atoi(argv[1]);
    } else if (argc == 3) {
        port = atoi(argv[1]);
        backlog = atoi(argv[2]);
    } else {
        printf("Usage: ./cservd <port> <backlog>\n");
        return -1;
    }
    
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
        
        pid = fork();
        if(!pid) {
            ret = read(csock, buf, sizeof(buf));
            if(ret <= 0) {
                printf("Did not receive any data from client");
                close(csock);
            } else {
                printf("Recieved %d bytes, saying: %s\n", ret, buf);
                char *data = "cserverd in session";
                write(csock, data, sizeof(data));
            }
        }
    }

    return 0;
}
