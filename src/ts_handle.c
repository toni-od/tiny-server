/* ts_handle.c */

#include "header.h"

int ts_handle(int csock) {
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
        const char *data = 
            "HTTP/1.1 200 OK\r\n"
            "Content-Type: text/html\r\n"
            "Connection: close\r\n"
            "\r\n"
            "<html><body><h1>Hello, World!</h1></body></html>";
        // char *data = "HTTP/1.0 200 OK\r\nContent-Type: text/html\r\n\r\n<!DOCTYPE html><html><body><h1>Hello from tiny-server!</h1></body></html>\r\n";
        write(csock, data, strlen(data));
    }
    // free up resources
    close(csock);
    return 0;
}
