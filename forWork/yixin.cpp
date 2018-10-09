#include <bits/stdc++.h>
using namespace std;
long long mod = 100003; 
long long multi(long long a, long long b, long long c) { 
    long long ret = 0; 
    while(b) { 
        if(b & 1) { 
            ret += a; 
            if(ret >= c) 
                ret -= c; 
        } 
        a += a; 
        if(a >= c) 
            a -= c; 
            b >>= 1; 
            } 
        return ret; 
} 
long long fastmod(long long a, long long b, long long c)//a^b mod c 
{ 
    long long ret = 1; 
    a %= c; for (; b; b >>= 1, a = multi(a, a, c)) 
    if (b & 1) 
    ret = multi(ret, a, c); 
    return ret; 
} 

int main(){
    long long int N,W;
    cin>>N>>W;
    long long int res = N*(W-1)%100003;
    cout<<res<<endl;
}
/*
//逆序对的数目
int main(){
    int n;
    cin>>n;
    vector<int> arr(n,0);
    for(int i=0;i<n;i++)
        cin>>arr[i];
    
    int sum=0;
    for(int i=0;i<n-1;i++){
        for(int j=i+1;j<n;j++){
            if(arr[i]>arr[j]) 
                sum++;
        }
    }
    cout<<sum<<endl;
    return 0;
}*/