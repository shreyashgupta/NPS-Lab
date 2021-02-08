#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>

int main()
{
    int fd,addrlen=sizeof(struct sockaddr_in);

    if((fd=socket(AF_INET,SOCK_DGRAM,0))<0)
    {
        perror("socket");
        exit(0);
    }
    printf("Socket created\n");
    struct sockaddr_in servaddr,cliaddr;
    servaddr.sin_family=AF_INET;
    servaddr.sin_port=htons(8000);
    servaddr.sin_addr.s_addr=INADDR_ANY;
    if(bind(fd,(struct sockaddr*)&servaddr,sizeof(servaddr))<0)
    {
        perror("bind");
        exit(0);
    }
    printf("Socket bound\n");
    char buffer[1024];
    while(1)
    {
        memset(buffer,0,sizeof(buffer));
        recvfrom(fd,buffer,sizeof(buffer),0,(struct sockaddr*)&cliaddr,&addrlen);
        printf("Recieved from %d\n",cliaddr.sin_family);
        sendto(fd,buffer,sizeof(buffer),0,(struct sockaddr*)&cliaddr,addrlen);
    }

}