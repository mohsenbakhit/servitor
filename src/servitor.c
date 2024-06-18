#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <netinet/in.h>
#define PORT 8080

int main(int argc, char const** argv) {
	// AF_LOCAL is for processes on the same host
	// AF_INET is for IPv4, and AF_INET6 is for IPv6
	int server_fd, new_socket;
	struct sockaddr_in address;
	socklen_t addrlen = sizeof(address);
	int opt = 1;
	int port = atoi(argv[1]);
	if (server_fd = socket(AF_INET, SOCK_STREAM, 0) < 0) {
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
}
