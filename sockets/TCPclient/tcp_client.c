#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/socket.h>

#include <unistd.h>

#include <netinet/in.h>

int main()
{
    //---------------------------------------CREATE A SOCKET------------------------------------------
    //integer that holds the socket descriptor (information of the socket)
    int network_socket;

    //call the socket function
    //first parameter is the domain of the socket, second is the type of the socket (tcp, connection), the last parameter specifies the protocol (0 is default for tcp)
    network_socket = socket(AF_INET, SOCK_STREAM, 0);

    //---------------------------------------SPECIFY AN ADDRESS F0R THE SOCKET------------------------------------------
    struct sockaddr_in server_address;

    server_address.sin_family = AF_INET; //what type of address we are working with
    server_address.sin_port = htons(9002); //this function converts the port number to the approriate data
    server_address.sin_addr.s_addr = INADDR_ANY; // INADDR_ANY will resolve to any ip address in the local machine

    //call the connect function
    //first par is the socket itself, 
    int connection_status = connect(network_socket, (struct sockaddr *) &server_address, sizeof(server_address));

    if (connection_status == -1) {
        printf("There was an error while connecting to the remote socket\n\n");
    }

    //when receiving data from the server
    //first parameter is the socket, second is a string to hold info we might get from the server (the location of where we hold it), third is the size of the buffer (how much space we need)
    char server_response[256];
    recv(network_socket, &server_response, sizeof(server_response), 0);

    //print out the data we get back from the server
    printf("The server sent the data: %s\n", server_response);

    //closing the socket after we're done. Takes one parameter and that's the socket
    close(network_socket);

    return 0;
}
