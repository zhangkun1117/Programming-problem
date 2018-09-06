#include <bits/stdc++.h>
using namespace std;
/*
//4:AC
int main(){
    string first;
    string second;
    getline(cin,first);
    getline(cin,second);
    // cin>>first;
    // cin>>second;
    vector<vector<int>> arr(first.size()+1,vector<int>(second.size()+1,0));
    int mlen =0;
    for(int i=0;i<first.size();i++){
        for(int j=0;j<second.size();j++){
            if(first[i] == second[j]){
                arr[i+1][j+1] = arr[i][j]+1;
                mlen = arr[i+1][j+1]>mlen?arr[i+1][j+1]:mlen;
            }
        }
    }
    cout<<mlen<<endl;
    return 0;    
}*/
//3
/* AC 
int main(){
    int n;
    while(cin>>n){
        vector<long int> arr(n);
        for(int i=0;i<n;i++){
            cin>>arr[i];
        }
        long  max =0;
        for(int i=1;i<n;i++){
            for(int j=i-1,ilen = arr[i];j>=0;j--){
                ilen = ilen<arr[j]?ilen:arr[j];
                max = (ilen*(i-j+1) >max)?ilen*(i-j+1):max;
            }
        }
        cout<<max<<endl;
    }
}*/

//2. 未通过
int main(){
    int N = 0;
    cin >> N;
    long long * F = new long long[N + 1]();
    int c[6] = { 1, 5, 10, 20, 50, 100 };
  
    F[0] = 1;
    for (int i = 0; i < 6; i++)
        for (int v = c[i]; v <= N; v++){
            F[v] = F[v] + F[v - c[i]];
        }
    cout << F[N]<<endl;
    return 0;
}

/*//1. AC
int main(){
	int n;
	while (cin >> n){
        cout<<pow(2,n-1)<,endl;
	}
	return 0;
}*/
