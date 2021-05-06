#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main() {
        char server_msg[1024] = "Successfully connected to the Server.";

        int server_socket = socket(AF_INET, SOCK_STREAM, 0);

        struct sockaddr_in server_address;

        server_address.sin_family = AF_INET;
        server_address.sin_port = htons(18000);
        server_address.sin_addr.s_addr = INADDR_ANY;

        bind(server_socket, (struct sockaddr *)&server_address, sizeof(server_address));

	listen(server_socket, 5);

	int new_socket = accept(server_socket, NULL, NULL);

        send(new_socket, &server_msg, sizeof(server_msg), 0);

        close(server_socket);

        return 0;
}
