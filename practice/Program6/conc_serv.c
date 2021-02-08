#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
#include<arpa/inet.h>
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
}
int main()
{
    int listenfd,connfd,addrlen=sizeof(struct sockaddr_in);
    struct sockaddr_in servaddr,cliaddr;
    if((listenfd=socket(AF_INET,SOCK_STREAM,0))<0)
    {
        perror("socket");
        exit(0);
    }
    printf("Socket Created\n");
    servaddr.sin_port=htons(8000);
    servaddr.sin_family=AF_INET;
    servaddr.sin_addr.s_addr=INADDR_ANY;
    if(bind(listenfd,(struct sockaddr*)&servaddr,sizeof(servaddr))<0)
    {
        perror("binding");
        exit(0);
    }
    printf("Socket Bound\n");
    if(listen(listenfd,10)<0)
    {
        perror("listen");
        exit(0);
    }
    printf("listening\n");
    while(1)
    {
        if((connfd=accept(listenfd,(struct sockaddr*)&cliaddr,&addrlen))<0)
        {
            perror("accept");
            exit(0);
        }  
        printf("Accepted connection from %s\n",inet_ntoa(cliaddr.sin_addr));
        int pid;
        if((pid=fork())==0)
        {
            cli(connfd);
        }
        close(connfd);
    }


}