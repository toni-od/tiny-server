/* ts_accept.c */

#include "header.h"

/*
* ts_accept/1
*
* input:
*   serv_sock - a tcp socket rep the server
* output:
*   c - a connected client socket or 0 on failure
*/
int ts_accept(int serv_sock) {
    int client_sock;
    struct sockaddr_in c_addr;
    socklen_t c_addr_len = 0;
    
    client_sock = accept(serv_sock, (struct sockaddr *)&c_addr, &c_addr_len);
    if(client_sock < 0) {
        return 0;
    }
    return client_sock;
}
