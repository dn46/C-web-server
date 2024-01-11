#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/socket.h>

#include <unistd.h>

#include <netinet/in.h>

int main() {

    // hold info and read from a file

    //file pointer to hold the data
    FILE *html_data;
    //open the html file to read it; first parameter is the file itself, second is how to use the file (write, read)
    html_data = fopen("index.html", "r");

    //get the size of the html file
    fseek(html_data, 0, SEEK_END);
    long fsize = ftell(html_data);
    fseek(html_data, 0 ,SEEK_SET);

    //allocate memory for the response data and the http header
    char *response_data = malloc(fsize + 1);
    char *http_header = malloc(2048 + fsize + 1);

    //response with the status code
    strcpy(http_header, "HTTP/1.1 200 OK\r\n\n");

    //read the file; first parameter is where we will read the data to, second is how much data to read, last is the file we're reading from
    while (fgets(response_data, fsize, html_data))
    {   
        //concatenate the header and the data of the file
        strcat(http_header, response_data);
    }

    //create a socket
    int server_socket;
    server_socket = socket(AF_INET, SOCK_STREAM, 0);

    //define the address
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(8001);
    server_address.sin_addr.s_addr = INADDR_ANY;

    //binding the socket to a port
    bind(server_socket, (struct sockaddr *) &server_address, sizeof(server_address));

    //listen for connections on that socket
    listen(server_socket, 5);

    //placeholder for the client socket
    int client_socket;

    //while loop for the server to continue responding to requests
    while (1)
    {
        //accept the connection on the client socket
        client_socket = accept(server_socket, NULL, NULL);

        //send data back to the client
        send(client_socket, http_header, strlen(http_header), 0);

        close(client_socket);
    }

    free(response_data);
    free(http_header);
    
    return 0;

}