/* http_parser.c */

#include "header.h"

Request *http_parse_request(char *str) {
    Request *r;
    char *p, *temp;
    
    r = (Request *)malloc(sizeof(Request));
    memset(r, 0, sizeof(Request));
    
    // extract http method
    // a http method is less than or equal to 7
    for(p = str; *p && *p != ' '; p++);
    temp = p+1;
    *p = 0;
    strncpy(r->method, str, 7);
    str = temp; // advance str
    
    // extract the url
    // url is only allowed to be 128 in length
    // including the null-terminator
    for(p = str; *p && *p != ' '; p++);
    temp = p+1;
    *p = 0;
    strncpy(r->url, str, 127);
    str = temp;
    
    // extract scheme
    // scheme e.g HTTP/1.0
    for(p = str; *p && (*p != '\r' || *p != '\n'); p++) {
        if(*p == '\r') p++; // advance pointer beyond CR character onto the LF
    }
    temp = p+1;
    *p = '\0';
    strncpy(r->scheme, str, 9);
    str = temp;
    
    return r;
}
