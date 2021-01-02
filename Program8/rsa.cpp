#include<bits/stdc++.h>

using namespace std;
#define ll long long

ll isprime(long int a)
{
    int i;
    for(i = 2; i< a; i++){
        if((a % i) == 0)
        return 0;
    }
    return 1;
}

ll  encrypt(char ch, long int n, long int e)
{
    int i;
    //cout<<ch<<" "; 
    ll  temp = ch;
    for(i = 1; i< e; i++)
        temp = (temp * ch) % n;
    return temp;
}

char decrypt(long int ch, long int n, long int d)
{
    int i;
    ll  temp = ch;
    for(i = 1; i< d; i++)
        ch =(temp * ch) % n;
    return ch;
}

int main()
{
    ll i, len;
    ll  p, q, n, phi, e, d;
    string message;
    
    cout<< "Enter the text to be encrypted: ";
    cin>>message;
    vector<int>cipher(message.size());
    len = message.size();
    do  {
            p = rand() % 50;
        } 
        while (!isprime(p));
    do  {
            q = rand() % 50;
        } 
        while (!isprime(q));
    n = p * q;
    phi = (p - 1) * (q - 1);
    do  {
            e = rand() % phi;
        } 
        while (__gcd(phi, e) != 1);
    do  {
            d = rand() % phi;
        } 
        while (((d * e) % phi) != 1);
    // cout<<"p : "<<p<<"  "<<"q : "<<q<<endl;
    // cout<<"n : "<<n<<endl;
    // cout<<"phi(n) : "<< phi<<endl;
    // cout<< "Public key (n,  e): (" << n << ", " << e << ")\n";
    // cout<< "Private key (n, d): (" << n << ", " << d << ")\n";
    for (i = 0; i<len; i++)
        cipher[i] = encrypt(message[i], n, e);
    cout<< "Encrypted message: ";
    
    for (i = 0; i<len; i++)
        cout<< cipher[i];
    
    for (i = 0; i<len; i++)
        message[i] = decrypt(cipher[i], n, d);
    cout<<endl;
    cout<< "Decrypted message: ";
    for (i = 0; i<len; i++)
        cout<< message[i];
    cout<<endl;
    return 0;
}