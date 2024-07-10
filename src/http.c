#include "http.h"
#include <string.h>
#include <stdio.h>

void parse_request(char* raw_request, struct HTTP_Request* req) {
    struct HTTP_Request req;
    char *line = strtok(raw_request, "\r\n");
    sscanf(line, "%s %s %s", req->method, req->path, req->http_version);

    req->header_count = 0;
    while ((line = strtok(NULL, "\r\n")) && strlen(line) > 0) {
        sscanf(line, "%[^:]: %[^\r\n]", req->headers[req->header_count][0], req->headers[req->header_count][1]);
        req->header_count++;
    }

    if ((line = strtok(NULL, ""))) {
        req->body = malloc(sizeof(line));
        strncpy(req->body, line, sizeof(req->body));
    }
}

void create_response(struct HTTP_Response res, const char* body) {

}
