#include<stdio.h>

unsigned fields[10];

unsigned short checksum()
{
    int i;
    int sum=0;
    printf("Enter IP header information in 16 bit words\n");
    for(int i=0;i<9;i++)
        scanf("%x",&fields[i]);
    // for(int i=0;i<9;i++)
    //     cout<<fields[i]<<" ";
    for(i=0;i<9;i++){
        
        sum=sum+(unsigned short)fields[i];

        while(sum>>16)
        sum=(sum&0xFFFF)+(sum>>16);

    }
    sum=~sum;
    return (unsigned short)sum;
}

int main(){
    unsigned short result1,result2;

    result1=checksum();
    printf("\ncomputed checksum at sender %x\n",result1);
    result2=checksum();
    printf("\ncomputed checksum at reciever %x\n",result2);

    if(result1==result2){
        printf("NO ERROR\n");
    }
    else{
        printf("ERROR detected\n");
    }
}