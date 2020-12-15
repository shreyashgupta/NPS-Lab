#include<stdio.h>
#include<bits/stdc++.h>
using namespace std;

int calc_red(int pos,vector<int>codeword)
{
    int ret=0;
    int pos1=log2(pos);
    for(int i=1;i<=codeword.size();i++)
    {
        // cout<<codeword[i-1];
        if((i&(1<<pos1)) && (i&(i-1)))
        {
            ret^=codeword[i-1];
        }
    }
    cout<<"r"<<pos1<<" : "<<ret<<endl;
    return ret;
}
vector<int>hammingcode(vector<int>&message)
{
    cout<<"\nRedundant bits are : \n\n";
    int r=3; //for 4 bit message
    int m=message.size();
    int n=r+m;
    vector<int>codeword(n,-1);
    int j=0;
    reverse(message.begin(),message.end());
    for(int i=1;i<=n;i++)
    {
        if(i&(i-1))
        {
            codeword[i-1]=message[j++];
        }
    }

    for(int i=1;i<=n;i++)
    {
        if(!(i&(i-1)))
        {
            codeword[i-1]=calc_red(i,codeword);
        }
    }
    reverse(codeword.begin(),codeword.end());
    return codeword;
}
int calc_syn(int pos,vector<int>codeword)
{
    int ret=0;
    int pos1=log2(pos);
    for(int i=1;i<=codeword.size();i++)
    {
        if((i&(1<<pos1)) && (i&(i-1)))
        {
            ret^=codeword[i-1];
        }
    }
    ret^=codeword[pos-1];
    cout<<"s"<<pos1<<" : "<<ret<<endl;
    return ret;
}
bool checker(vector<int>v)
{
    cout<<"Syndromes are : \n\n";
    int n=v.size();
    int pos=0;
    reverse(v.begin(),v.end());
    for(int i=1;i<=n;i++)
    {
        if(!(i&(i-1)))
        {
            int s=calc_syn(i,v);
            pos+=s*i;
        }
    }
    if(pos==0)
        cout<<"\nNo error\n";
    else
        cout<<"\nError as position "<<pos<<endl;
    cout<<"Corrected code : \n";
    for(int i=0;i<n;i++)
    {
        if(i==pos-1)
            v[i]=!v[i];
        cout<<v[i]<<" ";
    }

}
int main(){
    vector<int>v(4);
    cout<<"enter 4 bit codeword(add space)\n\n";
    for(int i=0;i<4;i++)
        cin>>v[i];
    vector<int>res=hammingcode(v);
    cout<<endl<<"Hamming code at sender :   ";
    for(int i=0;i<res.size();i++)
        cout<<res[i]<<" ";
    cout<<endl;
    vector<int>send={1,0,1,0,1,0,1};


    cout<<endl<<"Hamming code at reciever : ";
    for(int i=0;i<send.size();i++)
        cout<<send[i]<<" ";
    cout<<endl<<endl;
    checker(send);
}