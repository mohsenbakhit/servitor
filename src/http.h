#ifndef HTTP_H
#define HTTP_H
#define MAX_HEADERS 20
#define MAX_HEADERS_LEN 256

struct HTTP_Request {
    char method[16];
    char path[256];
    char http_version[16];
    char headers[MAX_HEADERS][4][MAX_HEADERS_LEN];
    int header_count;
    char* body;
};

struct HTTP_Response {
    char http_version[16];
    int status_code;
    char reason_phrase[8];
    char headers[MAX_HEADERS][4][MAX_HEADERS_LEN];
    int header_count;
    char* body;
};

void parse_request(char* request_str, struct HTTP_Request* req);

void create_response(struct HTTP_Response *res, const char* body);

void send_http_response(int client_socket, const struct HTTP_Response* res);
#endif //HTTP_H
