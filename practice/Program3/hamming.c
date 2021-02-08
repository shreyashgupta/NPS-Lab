#include<stdio.h>


void coder(char data[],char res[])
{
    // 7  6  5  4  3  2  1
    // d3 d2 d1 r2 d0 r1 r0
    //0  1  2  3  4  5  6  
    res[0]=data[0];
    res[1]=data[1];
    res[2]=data[2];
    res[4]=data[3];
    res[6]=(data[3]-'0')^(data[2]-'0')^(data[0]-'0')+'0';
    res[5]=(data[3]-'0')^(data[1]-'0')^(data[0]-'0')+'0';
    res[3]=(data[2]-'0')^(data[1]-'0')^(data[0]-'0')+'0';
    return ;
}
void checker(char res[])
{
    int s0=(res[4]^res[2]^res[0]) ^ res[6];
    printf("S0 : %d",s0);
    int s1=(res[4]^res[1]^res[0]) ^ res[5];
    printf("\nS1 : %d",s1);
    int s2=(res[1]^res[2]^res[0]) ^ res[3];
    printf("\nS2 : %d\n",s2);
}
int main()
{
    char s[4];
    printf("Enter data word : ");
    scanf("%s",s);
    char coded[7];
    coder(s,coded);
    printf("codeword: %s\n",coded);
    coded[5]='1';
    printf("\n");
    checker(coded);
    return 0;
}