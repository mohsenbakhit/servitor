#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <netinet/in.h>
#include "http.h"
#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
	// AF_LOCAL is for processes on the same host
	// AF_INET is for IPv4, and AF_INET6 is for IPv6
	int server_fd, new_socket;
	ssize_t valread;
	struct sockaddr_in address;
	socklen_t addrlen = sizeof(address);
	const int opt = 1;
	const int port = 8080;
	char buffer[BUFFER_SIZE];
	if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		perror("ERROR: Socket failed");
		exit(EXIT_FAILURE);
	}

	if (setsockopt(server_fd, SOL_SOCKET,
			   SO_REUSEADDR | SO_REUSEPORT, &opt,
			   sizeof(opt))) {
		perror("setsockopt");
		exit(EXIT_FAILURE);
			   }
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(port);

	if (bind(server_fd, (struct sockaddr*)&address, addrlen) < 0) {
		perror("Error: Bind failed");
		exit(EXIT_FAILURE);
	}
	
	if (listen(server_fd, 3) < 0) {
		perror("Error: Listen failed");
		exit(EXIT_FAILURE);
	}

	if ((new_socket = accept(server_fd, (struct sockaddr*)&address, &addrlen)) < 0) {
		perror("Error: Could not accept conn");
		exit(EXIT_FAILURE);
	}

	valread = read(new_socket, buffer, BUFFER_SIZE - 1);
	if (valread < 0) {
		perror("Error: Failed to recv ");
		exit(EXIT_FAILURE);
	}
	buffer[valread] = '\0';
    struct HTTP_Request *req = (struct HTTP_Request *)malloc(sizeof(struct HTTP_Request));
    struct HTTP_Response *res = (struct HTTP_Response *)malloc(sizeof(struct HTTP_Response));	if (!req || !res) {
        perror("Error: Memory allocation failed");
        exit(EXIT_FAILURE);
    }

	printf("%s\n", buffer);
	parse_request(buffer, req);
	create_response(res, req->body);
	send_http_response(new_socket, res);
	printf("message sent!\n");

	free(req);
	free(res);
	close(new_socket);
	close(server_fd);

	return 0;
}	
