#ifndef HTTP_H
#define HTTP_H

struct HTTP_Request {
    char* method;
    char* path;
    char* http_version;
};

struct HTTP_Response {

};
struct HTTP_Request parse_request(char* request_str);
#endif //HTTP_H
