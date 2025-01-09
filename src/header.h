#ifndef _TS_H
#define _TS_H

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int ts_accept(int serv_sock);
int ts_listen(char *ip, int port, int backlog);

#endif // _TS_H