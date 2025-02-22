/*Server*/
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<sys/stat.h>
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<fcntl.h>
#include<string.h>
int main()
{
    int cont,create_socket,new_socket,addrlen,fd;
    int bufsize = 1024;
    char *buffer = malloc(bufsize);
    char fname[256];
    struct sockaddr_in address;
    if ((create_socket = socket(AF_INET,SOCK_STREAM,0)) > 0)
        printf("The socket was created\n");

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(8000);

    if (bind(create_socket,(struct sockaddr *)&address,sizeof(address)) == 0)
        printf("Binding Socket\n");
    listen(create_socket,3);
    
    addrlen = sizeof(struct sockaddr_in);
    new_socket = accept(create_socket,(struct sockaddr *)&address,&addrlen);

    while(1)
    {
        FILE *fpipe;
        char c = 0;
        recv(new_socket,fname, 255,0);
        if(!strcmp(fname,"end"))
            break;
        if(strlen(fname))
        {
            printf("A request for Command { %s } Received..\n\n", fname);
            if (0 == (fpipe = (FILE*)popen(fname, "r")))
            {
                perror("popen() failed.");
                exit(EXIT_FAILURE);
            }
            char buffer[1000];
            int i=0;
            while (fread(&c, sizeof c, 1, fpipe))
            {
                buffer[i++]=c;
            }
            buffer[i]='\0';
            puts(buffer);
            send(create_socket, buffer, sizeof(buffer), 0);
            printf("\nRequest Completed\n");
        }
    }
    close(new_socket);
    return close(create_socket);
}
