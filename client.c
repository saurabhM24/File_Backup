#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main() {
	char server_response[1024] = {'\0'};

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

	close(client_socket);

	return 0;
}
