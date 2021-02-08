
#include<stdio.h>

unsigned short fields[9];

unsigned short checksum()
{
    printf("Enter IP header in 16 bit words : ");
    for(int i=0;i<9;i++)
        scanf("%x",&fields[i]);

    int sum=0;

    for(int i=0;i<9;i++)
    {
        sum+=fields[i];
        while(sum>>16)
            sum=(sum&(0xFFFF))+ (sum>>16);
    }
    sum=~sum;

    return (unsigned short)sum;
}
int main()
{
    printf("Client side\n");

    int r1=checksum();
    printf("%x\n",r1);
    printf("Server side\n");
    
    int r2=checksum();
    printf("%x\n",r2);
    if(r1==r2)
        printf("NO ERROR\n");
    else
        printf("Error detected\n");


}
