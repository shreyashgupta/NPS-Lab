#include<unistd.h>
#include<stdio.h>
#include<sys/socket.h>
#include<string.h>
#include<stdlib.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>
int main(int argc,char*argv[])
{
    int connfd;
    struct sockaddr_in addr;

    addr.sin_family=AF_INET;
    addr.sin_port=htons(8000);
    inet_pton(AF_INET,argv[1],&addr.sin_addr);
    connfd=socket(AF_INET,SOCK_STREAM,0);
    if(connfd<=0)
    {
        printf("error creating socket\n");
        exit(0);
    }
    printf("socket created\n");
    if(connect(connfd,(struct sockaddr*)&addr,sizeof(addr))==0)
        printf("connected to %s\n",argv[1]);
    else
    {
        printf("error connecting\n");
        exit(0);   
    }

    
    char buffer[1024];
    printf("Enter filename : ");
    
    char* hello;
    gets(hello);
    puts(hello);
    memset(buffer,0,sizeof(buffer));
    // read(connfd,buffer,1024);
    // printf("%s\n",buffer);
    send(connfd,hello,sizeof(hello),0);
    while(read(connfd,buffer,1024))
        puts(buffer);
    close(connfd);
}