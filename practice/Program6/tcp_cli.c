#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<netinet/in.h>
#include<unistd.h>
#include<sys/socket.h>
#include<arpa/inet.h>
void echo(int connfd)
{
    char buffer[1024];
    while(1)
    {
        scanf("%s",buffer);
        send(connfd,buffer,sizeof(buffer),0);
        memset(buffer,0,sizeof(buffer));
        if(!recv(connfd,buffer,sizeof(buffer),0))
            break;
        printf("%s\n",buffer);
    }
    close(connfd);
}
int main(int argc,char*argv[])
{
    int fd,addrlen=sizeof(struct sockaddr_in);
    struct sockaddr_in addr;

    if((fd=socket(AF_INET,SOCK_STREAM,0))<0)
    {
        perror("socket");
        exit(0);
    }
    printf("Socket created\n");
    addr.sin_family=AF_INET;
    addr.sin_port=htons(8000);

    inet_pton(AF_INET,argv[1],&addr.sin_addr.s_addr);
    if(connect(fd,(struct sockaddr*)&addr,sizeof(addr))<0)
    {
        perror("connect");
        exit(0);
    }
    printf("socket connected\n");
    echo(fd);
    return 0;

}