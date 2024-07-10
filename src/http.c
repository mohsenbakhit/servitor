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

void create_response(struct HTTP_Response *res, const char* body) {
    strcpy(res->http_version, "HTTP/1.1");
    res->status_code = 200;
    strcpy(res->reason_phrase, "OK");

    res->header_count = 0;
    strcpy(res->headers[res->header_count][0], "Content-Type");
    strcpy(res->headers[res->header_count][1], "text/html");
    res->header_count++;

    sprintf(res->headers[res->header_count][0], "Content-Length");
    sprintf(res->headers[res->header_count][1], "%lu", strlen(body));
    res->header_count++;

    strcpy(res->body, body);
}

void send_http_response(int client_socket, const struct HTTP_Response* res) {
    char response_buffer[2048];
    int offset = sprintf(response_buffer, "%s %d %s\r\n", res->http_version, res->status_code, res->reason_phrase);

    for (int cur_header = 0; cur_header < res->header_count; cur_header++) {
        offset += sprintf(response_buffer + offset, "%s: %s\r\n", res->headers[cur_header][0], res->headers[cur_header][1]);
    }

    offset += sprintf(response_buffer + offset, "\r\n");
    offset += sprintf(response_buffer + offset, "%s", res->body);

    send(client_socket, response_buffer, strlen(response_buffer), 0);
}
