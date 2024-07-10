#include "http.h"
#include <string.h>
#include <stdio.h>
struct HTTP_Request parse_request(char* request_str) {
    struct HTTP_Request req;
    req.method = strtok(request_str, " ");
    req.path = strtok(NULL, " ");
    req.http_version = strtok(NULL, " ");
    return req;
}

struct HTTP_Response send_response(struct HTTP_Request req) {
    struct HTTP_Response res;
    return res;
}
