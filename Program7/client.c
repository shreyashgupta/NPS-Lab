/*Client*/
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<stdio.h>
int main(int argc,char *argv[])
{
    int create_socket,cont;
    int bufsize = 1024;
    char *buffer = malloc(bufsize);
    char fname[256];
    struct sockaddr_in address;

    if ((create_socket = socket(AF_INET,SOCK_STREAM,0)) > 0)
        printf("The Socket was created\n");
    address.sin_family = AF_INET;
    address.sin_port = htons(8000);

    inet_pton(AF_INET,argv[1],&address.sin_addr);

    if (connect(create_socket,(struct sockaddr *) &address, sizeof(address)) == 0)
        printf("The connection was accepted with the server %s...\n",argv[1]);
    
    while(1)
    {
        printf("Enter The Command to Request : "); 
        gets(fname);
        send(create_socket, fname, sizeof(fname), 0);
        if(!strcmp(fname,"end"))
            break;
    }
    //printf("The contents of file are...\n\n");
    int flag=0;
    printf("\nEOF\n");
    return close(create_socket);
}