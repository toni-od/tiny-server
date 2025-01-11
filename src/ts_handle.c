/* ts_handle.c */

#include "header.h"

int ts_handle(int csock) {
    int ret;
    char buf[1024];
    char payload[1024];
    
    ret = read(csock, buf, sizeof(buf));
    if(ret <= 0) {
        printf("Did not receive any data from client");
        close(csock);
        return -1;
    } else {
        ret--;
        buf[ret] = 0;
        
        //printf("Recieved %d bytes, saying: %s\n", ret, buf);
        // TODO: send a copy of buff to preferably
        // maintain the original http request 
        Request *req = http_parse_request(buf);
        if(req) {
            // printf("Method: %s\n", req->method);
            // printf("Url: %s\n", req->url);
            // printf("Scheme: %s\n", req->scheme);
            
            memset(payload, 0, strlen(payload));
            sprintf(payload, "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\nConnection: close\r\n\r\n<html><body><h1>Request details</h1><div>Method: %s</div><div>Url: %s</div><div>Scheme: %s</div></body></html>", req->method, req->url, req->scheme);
            free(req);
        }
        write(csock, payload, strlen(payload));
    }
    // free up resources
    close(csock);
    return 0;
}
