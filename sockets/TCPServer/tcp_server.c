#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/socket.h>

#include <unistd.h>

#include <netinet/in.h>

int main() {

    //string to hold the data to send to the clients
    char server_message[256] = "You have reached the server";

    //creating the socket
    int server_socket;

    server_socket = socket(AF_INET, SOCK_STREAM, 0);

    //define the server address struct
    struct sockaddr_in server_address;
    
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(9002);
    server_address.sin_addr.s_addr = INADDR_ANY;

    //bind the socket to our specified IP and port
    bind(server_socket, (struct sockaddr*) &server_address, sizeof(server_address));

    //listen function to start listening for connections
    listen(server_socket, 5);

    int client_socket;

    client_socket = accept(server_socket, NULL, NULL); //after we accept the connection we get a socket, creating a two way connection of sending and receiving data

    //send the message, first we pass the socket we are sending data on, then the data to be sent, and the size of the message
    send(client_socket, server_message, sizeof(server_message), 0);

    //close the socket
    close(server_socket);

    return 0;
}