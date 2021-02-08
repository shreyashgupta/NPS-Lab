#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<string.h>
#include<arpa/inet.h>
int main(int argc,char*argv[])
{
    int connfd,addrlen=sizeof(struct sockaddr_in);
    struct sockaddr_in addr;
    char buffer[1024]={};

    if((connfd=socket(AF_INET,SOCK_STREAM,0))<0)
    {
        perror("socket");
        exit(0);
    }
    bzero (&addr, sizeof (addr));
    printf("Created Socket\n");
    addr.sin_family=AF_INET;
    addr.sin_port=htons(9000);
    inet_pton(AF_INET,argv[1],&addr.sin_addr.s_addr);


    if(connect(connfd,(struct sockaddr*)&addr,sizeof(addr))<0)
    {
        perror("connect");
        exit(0);
    }
    printf("Connection established with %s\n",inet_ntoa(addr.sin_addr));
    while(1)
    {
        printf("Enter command : ");
        gets(buffer);
        send(connfd,buffer,sizeof(buffer),0);
        memset(buffer,0,sizeof(buffer));

        recv(connfd,buffer,sizeof(buffer),0);

        puts(buffer);
        printf("\n");
    }
    close(connfd);
    exit(0);
    
}