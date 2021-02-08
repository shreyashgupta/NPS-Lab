#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>

int main(int argc,char*argv[])
{
    int fd,addrlen=sizeof(struct sockaddr_in);

    if((fd=socket(AF_INET,SOCK_DGRAM,0))<0)
    {
        perror("socket");
        exit(0);
    }
    printf("Socket created\n");
    struct sockaddr_in addr;
    addr.sin_family=AF_INET;
    addr.sin_port=htons(8000);
    inet_pton(AF_INET,argv[1],&addr.sin_addr.s_addr);
    char buffer[1024];
    while(1)
    {
        
        scanf("%s",buffer);
        sendto(fd,buffer,sizeof(buffer),0,(struct sockaddr*)&addr,addrlen);
        memset(buffer,0,sizeof(buffer));
        recvfrom(fd,buffer,sizeof(buffer),0,NULL,NULL);
        printf("%s\n",buffer);
    }
    return 0;
}