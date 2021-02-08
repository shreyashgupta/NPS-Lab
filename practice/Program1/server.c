#include<unistd.h>
#include<stdio.h>
#include<sys/socket.h>
#include<string.h>
#include<stdlib.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>
int main()
{
    int connfd,listenfd;
    struct sockaddr_in servaddr,cliaddr;

    servaddr.sin_family=AF_INET;
    servaddr.sin_port=htons(8000);
    servaddr.sin_addr.s_addr=INADDR_ANY;
    listenfd=socket(AF_INET,SOCK_STREAM,0);
    if(listenfd<=0)
    {
        printf("error creating socket\n");
        exit(0);
    }
    printf("socket created\n");
    if(bind(listenfd,(struct sockaddr*)&servaddr,sizeof(servaddr))==0)
        printf("socket binded\n");
    else
    {
        printf("error binding\n");
        exit(0);   
    }
    printf("Listening at %s:%d\n",inet_ntoa(servaddr.sin_addr),servaddr.sin_port);
    listen(listenfd,1);
    int addrlen=sizeof(struct sockaddr_in);
    connfd=accept(listenfd,(struct sockaddr*)& cliaddr,&addrlen);
    printf("Connected to %s:%d\n",inet_ntoa(cliaddr.sin_addr),cliaddr.sin_port);
    
    char buffer[1024]={0};

    recv(connfd,buffer,sizeof(buffer),0);
    printf("Request for %s\n",buffer);
    FILE* fptr=fopen(buffer,"r");
    while(fread(buffer,1,1024,fptr))
    {
        //puts(buffer);
        send(connfd,buffer,sizeof(buffer),0);
    }
    close(connfd);
}