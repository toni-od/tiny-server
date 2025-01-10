#include "header.h"

int main(int argc, char *argv[]) {
    int port = 9000;
    int backlog = 10;
    char *ip = "0.0.0.0"; // listen on all interfaces
    
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
    
    ts_serve(ip, port, backlog);
    return 0;
}
