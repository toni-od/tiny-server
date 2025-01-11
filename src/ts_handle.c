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
        
        // print request data to help with parsing the http request
        // printf("Recieved %d bytes, saying: %s\n", ret, buf);
        // TODO: send a copy of buff to preferably
        // maintain the original http request 
        Request *req = http_parse_request(buf);
        if(req) {
            printf("Method: %s\n", req->method);
            printf("Url: %s\n", req->url);
            printf("Scheme: %s\n", req->scheme);
            printf("Headers:\n");
            for (int i = 0; req->headers[i] != NULL; i++) {
                printf("  %s\n", req->headers[i]);
            }
             // Print the body if it exists
            if (req->body && req->content_length > 0) {
                printf("Body: %s\n", req->body);
            } else {
                printf("Body: <No body or empty body>\n");
            }
            
            memset(payload, 0, strlen(payload));
            sprintf(payload, "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\nConnection: close\r\n\r\n<html><body><h1>Request details</h1><div>Method: %s</div><div>Url: %s</div><div>Scheme: %s</div><div><form method='POST' action='/save'><label for='username'>Username</label><br/><input type='text' name='username'/><br/><label for='password'>Password</label><br><input type='password' name='password'/><br/><input type='submit' value='save'/></form></div></body></html>", req->method, req->url, req->scheme);
            http_free_request(req);
        }
        write(csock, payload, strlen(payload));
    }
    // free up resources
    close(csock);
    return 0;
}
