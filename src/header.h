#ifndef _TS_H
#define _TS_H

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

struct Request {
    char method[8];
    char url[128];
    char scheme[9];
    char **headers;
    char *body;
};
typedef struct Request Request;

Request *http_parse_request(char *str);

int ts_serve(char *ip, int port, int backlog);
int ts_accept(int serv_sock);
int ts_listen(char *ip, int port, int backlog);
int ts_handle(int csock);

#endif // _TS_H