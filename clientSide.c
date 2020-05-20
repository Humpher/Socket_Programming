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

    int readval;                                             //read value sent from the server side
    char *fileName = "Constitution.txt";                     //pointer to hold the specific file being requested from the server
    char buffer[128] = {0};                                 //buffer to hold the contents of the file sent from the server
    int cSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP); //client socket variable created
    struct sockaddr_in server_add;                           //Hold the address elements in the struct sockaddr_in
    char *userName = "";
    char *user = (char*)malloc(sizeof(char*));

    if (cSocket < 0) //Returns -1 if client socekt creation fails
    {
        DieWithError("socket() failed");
    }

    server_add.sin_family = AF_INET;                     //Internet protocol
    server_add.sin_port = htons(Port);                   //Address port, in this case 8080
    server_add.sin_addr.s_addr = inet_addr("127.0.0.1"); //Internet address, in this case the loop back address "127.0.0.1"

    if (connect(cSocket, (struct sockaddr *)&server_add, sizeof(server_add)) < 0)
    { // Connect to server; returns -1 if connection fails
        DieWithError("Error: Couldn't connect");
    }


    printf("Enter your username: ");
    userName = (char*)malloc(sizeof(char*));
    scanf("%s", userName);
    
    send(cSocket, userName, strlen(userName), 0); //Send user name to server
    printf("Submitting username to server...\n\n");


    /*send(cSocket, fileName, strlen(fileName), 0); //Send data requesting for the specific file from the server
    printf("Establishing a connection...\n\n");*/

    readval = read(cSocket, buffer, sizeof(buffer)/sizeof(buffer[0])); //Read the server's response and put into the buffer
    printf("\nThe users online are: %s\n", buffer);

    printf("Enter the full name (no characters) of the user you want to connect with:  ");
    scanf("%s", user);

    char *userSelected = strstr(buffer, user);
    if (userSelected != NULL) /* Substring found */
	{
		printf("'%s' is selected\n", user);
    send(cSocket, user, strlen(user), 0); //Send user name to server
    printf("Submitting username to server...\n\n");

	}
	else /* Substring not found */
	{
		printf("'%s' is not among the users: ",user);
	}
   
    return 0;

    close(cSocket);
}