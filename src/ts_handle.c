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
        char *data = "cserverd in session";
        write(csock, data, strlen(data));
    }
    // free up resources
    close(csock);
    return 0;
}
