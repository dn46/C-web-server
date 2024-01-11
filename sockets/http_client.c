#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/socket.h>

#include <unistd.h>

#include <netinet/in.h>
#include <arpa/inet.h>

int main(int argc, char const *argv[])
{

    if (argc != 2) {
        printf("Usage: %s <IP>\n", argv[0]);
        exit(1);
    }
    //grab the address of the server from the cli argument and store it in a pointer
    char *address;
    address = argv[1];

    int client_socket;
    client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket == -1) {
        perror("socket");
        exit(1);
    }

    struct sockaddr_in remote_address;
    remote_address.sin_family = AF_INET;
    remote_address.sin_port = htons(80);
    //first parameter is the address, second where we store it. 
    inet_aton(address, &remote_address.sin_addr.s_addr);

    connect(client_socket, (struct sockaddr *) &remote_address, sizeof(remote_address));

    //variables to hold request and response
    char request[] = "GET / HTTP/1.1\r\n\r\n";
    char response[4096];

    //send the request
    send(client_socket, request, sizeof(request), 0);

    //receive the response; we pass the address to store the response
    recv(client_socket, &response, sizeof(response), 0);

    printf("response from the server: %s\n", response);

    close(client_socket);

    return 0;
}
