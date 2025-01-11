/* http_parser.c */

#include "header.h"

Request *http_parse_request(char *str) {
    Request *r = (Request *)malloc(sizeof(Request));
    memset(r, 0, sizeof(Request));

    // extract HTTP method, move past the space after method
    char *p = str;
    while (*p && *p != ' ') p++;
    *p = '\0';
    strncpy(r->method, str, MAX_METHOD_LEN - 1);
    str = p + 1;

    // extract the URL, move past the space after URL
    p = str;
    while (*p && *p != ' ') p++;
    *p = '\0';
    strncpy(r->url, str, MAX_URL_LEN - 1);
    str = p + 1;

    // extract HTTP version (scheme), move past the \r\n after the scheme
    p = str;
    while (*p && *p != '\r' && *p != '\n') p++;
    *p = '\0';
    strncpy(r->scheme, str, MAX_SCHEME_LEN - 1);
    str = p + 2;

    // parse headers
    r->headers = malloc(sizeof(char *) * MAX_NUM_HEADERS);
    int index = 0;
    char *content_length_str = NULL;

    while (*str && index < MAX_NUM_HEADERS) {
        p = str;
        while (*p && *p != '\r') p++;
        if (*p == '\r') {
            *p = '\0';
            r->headers[index] = strdup(str); // Duplicate the header string
            // if we find the Content-Length header, postpone its parsing
            // save it in the content_length_str for later processing
            if (strncasecmp(r->headers[index], "Content-Length:", 15) == 0) {
                content_length_str = r->headers[index] + 15;
            }
            index++;
            str = p + 2; // Skip past the \r\n
        }

        // break if we reached the end of headers (empty line)
        if (*str == '\r' && *(str + 1) == '\n') {
            str += 2;
            break;
        }
    }

    // parse the body if Content-Length is not 0
    // TODO: handle off-by-one error in the body
    // printf("BODY [");
    // char *s;
    // for(s = str; *s; s++) {
    //     printf("%c", *s);
    // }
    // printf("]");
    if (content_length_str) {
        int content_length = atoi(content_length_str);
        r->body = malloc(content_length + 1);
        memcpy(r->body, str, content_length);
        r->body[content_length] = '\0';
        r->content_length = content_length;
    } else {
        r->body = NULL;
        r->content_length = 0;
    }

    return r;
}

void http_free_request(Request *r) {
    if (r == NULL) return;

    if (r->headers) {
        for (int i = 0; r->headers[i] != NULL; i++) {
            if(r->headers[i]) {
                free(r->headers[i]);
            }
        }
        free(r->headers);
    }

    if (r->body) {
        free(r->body);
    }

    free(r);
}
