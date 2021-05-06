#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>

#define SIZE 1024

int send_file(int sockfd, char *file_name);

int main() {
	char server_response[SIZE] = {'\0'};

	int client_socket = socket(AF_INET, SOCK_STREAM, 0);

	struct sockaddr_in server_address;

	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(18000);
        server_address.sin_addr.s_addr = inet_addr("10.210.77.140");


	int status = connect(client_socket, (struct sockaddr *)&server_address, sizeof(server_address));
	if (status == -1) {
		printf("Failed to connect to the server.");
		return 1;
	}

	recv(client_socket, &server_response, sizeof(server_response), 0);

	printf("Reponse from Server: %s\n", server_response);

	//file transfer
	status = send_file(client_socket, "test.txt");
	if (status != 0) {
		printf("Error in sending file data.");
		return 1;
	}

	printf("File has been successfully backed up.");	

	close(client_socket);

	return 0;
}

int send_file(int sockfd, char *file_name) {	
	char data[SIZE] = {'\0'};
	int status = 0;

	FILE *fp = fopen(file_name, "r");
	if (fp == NULL) {
		printf("Failed to open the file [%s].", file_name);
		return 1;
	}

	while (fgets(data, SIZE, fp) != NULL) {
		status = send(sockfd, data, sizeof(data), 0);
		if (status == -1) {
			return 1;
		}

		memset(data, 0, sizeof(data));
	}

	return 0;
}

