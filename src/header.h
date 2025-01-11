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

#define MAX_URL_LEN 128
#define MAX_METHOD_LEN 8
#define MAX_SCHEME_LEN 9
#define MAX_HEADER_LEN 512
#define MAX_NUM_HEADERS 20

typedef struct Request {
    char method[MAX_METHOD_LEN];
    char url[MAX_URL_LEN];
    char scheme[MAX_SCHEME_LEN];
    char **headers;
    char *body;
    int content_length;
} Request;
typedef struct Request Request;

Request *http_parse_request(char *str);
void http_free_request(Request *r);


int ts_serve(char *ip, int port, int backlog);
int ts_accept(int serv_sock);
int ts_listen(char *ip, int port, int backlog);
int ts_handle(int csock);

#endif // _TS_H