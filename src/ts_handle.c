#include "header.h"

int ts_handle(int ssock, int csock) {
    int ret;
    char buf[1024];
    
    ret = read(csock, buf, sizeof(buf));
    if(ret <= 0) {
        printf("Did not receive any data from client");
        close(csock);
        return -1;
    } else {
        ret--;
        buf[ret] = 0;
        printf("Recieved %d bytes, saying: %s\n", ret, buf);
        char *data = "HTTP/1.0 200 OK\r\n\r\n<!DOCTYPE html><html><body><h1>Hello from tiny-server!</h1></body></html>\r\n";
        write(csock, data, strlen(data));
    }
    // free up resources
    close(csock);
    return 0;
}
