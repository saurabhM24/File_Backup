#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>

#define SIZE 1024

int receive_file(int sockfd);

int main() {
        char server_msg[SIZE] = "Successfully connected to the Server.";

        int server_socket = socket(AF_INET, SOCK_STREAM, 0);

        struct sockaddr_in server_address;

        server_address.sin_family = AF_INET;
        server_address.sin_port = htons(18000);
        server_address.sin_addr.s_addr = INADDR_ANY;

        bind(server_socket, (struct sockaddr *)&server_address, sizeof(server_address));

	listen(server_socket, 5);

	int new_socket = accept(server_socket, NULL, NULL);

        send(new_socket, &server_msg, sizeof(server_msg), 0);

	int status = receive_file(new_socket);
	if (status != 0) {
		return 1;
	}

        close(server_socket);

        return 0;
}

int receive_file(int sockfd) {
	int count = 0;
	char data[SIZE] = {'\0'};

	FILE *fp = fopen("test.txt", "w");
	if (fp == NULL) {
		printf("Failed to open file.");
		return 1;
	}

	while (1) {
		count = recv(sockfd, data, sizeof(data), 0);
		if (count <= 0) {
			break;
		}
		
		fprintf(fp, "%s", data);
		memset(data, 0, sizeof(data));	
	}

	return 0;
}
