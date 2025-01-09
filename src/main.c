#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    struct sockaddr_in servaddr;
    int ssock, csock;
    int port = 9000;
    int backlog = 10;
    char *ip = "0.0.0.0";
    char buf[1024];
    int ret;
    socklen_t caddrlen;

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

    while(1) {
        csock = accept(ssock, (struct sockaddr*)&servaddr, &caddrlen);
        if(csock == -1) {
            perror("accept() error...");
        } else {
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
