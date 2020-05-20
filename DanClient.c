#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#define Port 8080
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include "dieError.h"
#define BUFFSIZE 2048 // buff size for read routine

int main(int argc, char *argv[])
{

    int valread = 0;
    char *hey = "Testing the second client";                   //read value sent from the server side
    char buffer[1024] = {0};                                   //buffer to hold the contents of the file sent from the server
    int cliSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP); //client socket variable created
    struct sockaddr_in server_add;                             //Hold the address elements in the struct sockaddr_in

    if (cliSocket < 0) //Returns -1 if client socekt creation fails
    {
        DieWithError("socket() failed");
    }

    server_add.sin_family = PF_INET;                     //Internet protocol
    server_add.sin_port = htons(Port);                   //Address port, in this case 8080
    server_add.sin_addr.s_addr = inet_addr("127.0.0.1"); //Internet address, in this case the loop back address "127.0.0.1"

    if (connect(cliSocket, (struct sockaddr *)&server_add, sizeof(server_add)) < 0)
    { // Connect to server; returns -1 if connection fails
        DieWithError("Error: Couldn't connect");
    }
    send(cliSocket, hey, strlen(hey), 0);
    printf("Message sent\n");
    valread = read(cliSocket, buffer, 1024);
    printf("%s\n", buffer);

    return 0;

    close(cliSocket);
}