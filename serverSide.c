#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#define Port 8080
#define MAXLISTEN 3
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <dirent.h>
#include "dieError.h"
#define NUMBER_OF_STRING 2 //the size of list of the usernames
#define MAX_STRING_SIZE 40 //maximum username size
#define MAX_BUFFSIZE 2048  //buff size for read routine

int main(int argc, char *argv[])
{
    int n;
    int filedp;                                                              //file descriptor value
    int readVal;                                                             //Read value from the client; contains the buffer from client
    char buffer[1024] = {0};                                                 //Initial buffer value to acknowledge the connection
    char fileBuff[1024] = {0}; 
    char userBuff[1024] = {0};                                              //file buffer to send the contents of the requested file
    int serverSocket = socket(PF_INET, SOCK_STREAM, 0);                      //Create server socket variable
    struct sockaddr_in add;                                                  //struct adddress variable to hold the family, address type and port number of sockets
    int clientSocket, newSocket;                                                        //hold client socket varibale
    int clientLen = sizeof(add);                                             //size of client address
    char *FDE = "File doesn't exist";                                        //File doesn't exist error message sent back to the client if it occurs
    char userNames[128];  //array to hold the usernames
    char *UDE = "Username doesn't exist on server";

    strcat(userNames, "Dan, Kathy");

    if (serverSocket < 0) //Returns negative -1 if it failed to create a socket variable
    {
        DieWithError("socket() failed");
    }

    add.sin_family = AF_INET;         //Internet protocol
    add.sin_addr.s_addr = INADDR_ANY; //Internet address, this if any
    add.sin_port = htons(Port);       //Address port, this case 8080 as defined above

    if (bind(serverSocket, (struct sockaddr *)&add, sizeof(add)) < 0) //Assign address to socket, return -1 if it failed
    {
        DieWithError("Failed: Could not bind port to socket");
    }

    if (listen(serverSocket, MAXLISTEN) < 0) //Listen for connection on the layer, return -1 if there is an error, MAXLISTEN: max length of queue connections
    {
        DieWithError("Failed: Could not listen");
    }

    //Accept connection from the client when requested.

    if ((clientSocket = accept(serverSocket, (struct sockaddr *)&add, (socklen_t *)&clientLen)) < 0) //Return -1 if it faled to accept the connection
    {
        DieWithError("Failed: Could not accept connection");
    }

    readVal = read(clientSocket, buffer, MAX_BUFFSIZE); //Read username sent from the client
    printf("\nConnected\n");
    printf("\nThe client's username is: %s\n", buffer);
    /*
    //Check to see if client asked for the specific filename
    if ((filedp = open(buffer, O_RDONLY)) == -1) // If true, open specific file, with the read only option; return -1 if file
                                                 //doesn't exist.
    {

        perror("Error");
        send(clientSocket, FDE, strlen(FDE), 0); //Send error to client if file doesn't exist in the directory
        exit(1);
    }
    int status;                                         //Hold the integer return value of the read function; return -1 if there is an error
    while ((status = read(filedp, fileBuff, 1024)) > 0) //Read and write to fileBuffer until EOF.
    {                                                   //File buffer contains the contents of the requested file
        ;
    }

    if (status == -1) //print out error if there is an error with the file
    {
        perror("Error");
    }*/

    

    if (strcmp(buffer, "Humphrey") == 0)
    {
        //send(clientSocket, userNames, sizeof(userNames), 0); //Send the client the list of current users on the network
        

    //printf("%c", tcp[0]);
        // Send the character array
     send(clientSocket, userNames, sizeof(userNames)/sizeof(userNames[0]),0);
     //read(clientSocket, userBuff, MAX_BUFFSIZE);
     //printf("Username selected is: %s\n", userBuff);
    }
    else
    {
        send(clientSocket, UDE, strlen(UDE), 0); //Send error to client if the name doesn't exist on the server
        exit(1);
    }
    //printf("\nThe number of bytes that have been sent: %lu bytes\n", strlen(fileBuff)); //Print out the number of bytes sent to the client

    //close(filedp); //close file open

    int pid;
    while (1) {
         newSocket = accept(serverSocket, (struct sockaddr *)&add, (socklen_t *)&clientLen);
         if (newSocket < 0)
                DieWithError("ERROR on accept");
         //fork new process
         pid = fork();
         if (pid < 0) {
              DieWithError("ERROR in new process creation");
         }
         if (pid == 0) {
            //child process
            close(clientSocket);
            //do whatever you want
            bzero(buffer, 256);
            n = read(newSocket, buffer, 255);
            if (n < 0)
                DieWithError("ERROR reading from socket");
            printf("Here is the message: %s\n", buffer);
            n = write(newSocket, "I got your message", 18);
            if (n < 0)
                 DieWithError("ERROR writing to socket");
            close(newSocket);
          } else {
             //parent process
             close(newSocket);
          }
    }

    return 0;
    close(serverSocket);
}