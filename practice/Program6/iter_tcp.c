#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<string.h>
#include<sys/types.h>
#include<netinet/in.h>

void cli(int connfd)
{
    char buffer[1024];
    while(1)
    {
        memset(buffer,0,sizeof(buffer));
        recv(connfd,buffer,sizeof(buffer),0);
        if(strcmp(buffer,"exit")==0)
            break;
        send(connfd,buffer,sizeof(buffer),0);
    }
    close(connfd);
    printf("Terminated Connection\n");
}

int main()
{
    int connfd,listenfd;
    char buffer[1024];
    struct sockaddr_in servaddr,cliaddr;
    if((listenfd=socket(AF_INET,SOCK_STREAM,0))<0)
    {
        perror("socket");
        exit(0);
    }
    printf("Socket Created\n");
    servaddr.sin_family=AF_INET;
    servaddr.sin_port=htons(8000);
    servaddr.sin_addr.s_addr=INADDR_ANY;
    if(bind(listenfd,(struct sockaddr*)&servaddr,sizeof(servaddr))<0)
    {
        perror("bind");
        exit(0);
    }
    printf("Socket bound\n");
    if(listen(listenfd,5)<0)
    {
        perror("listen");
        exit(0);
    }
    printf("Socket listening\n");
    int addrlen=sizeof(struct sockaddr_in);
    while(1)
    {
        if((connfd=accept(listenfd,(struct sockaddr*)&cliaddr,&addrlen))<0)
        {
            perror("connect");
            exit(0);
        }
        printf("Connected to %s\n",inet_ntoa(cliaddr.sin_addr));
        cli(connfd);
    }
}
