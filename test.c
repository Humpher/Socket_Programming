#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define NUMBER_OF_STRING 2
#define MAX_STRING_SIZE 40

int main(){
    char* userNAME = "";
    char usernames[NUMBER_OF_STRING][MAX_STRING_SIZE] ;

    strcpy(usernames[0], "Kathy");
    strcpy(usernames[1], "Dennis");

    /*printf("Enter your username: ");
    userNAME = (char*)malloc(sizeof(char*));
    scanf("%s", userNAME);
    printf("%s\n\n", userNAME);*/

   for(int i=0; i < NUMBER_OF_STRING; i++){
       printf("%s\n", usernames[i]);
   }

    

    
   
   // free(userNAME);
    return 0;
}
