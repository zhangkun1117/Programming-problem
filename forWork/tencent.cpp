#include <iostream>
#include <vector>
#include <numeric>
#include <limits>
#include <string>   
#include <set>
#include <algorithm>
#include <map>

using namespace std;

int main(){
    int n,m;
    cin>>n>>m;
    vector<vector<int>> arr(n,vector<int>(n,0));
    for(int i=0;i<m;i++){
        int u,v;
        cin>>u>>v;
        arr[u-1][v-1] = 1;    
    }
    int res =0;
    for(int i=0;i<n;i++){
        int  x,y=0;
        for(int j=0;j<n;j++){
            if(arr[j][i] ==1){
                x++;
            }
            if(arr[i][j] == 1){
                y++;
            }
        }
        if(x>y) res++;
    }
    cout<<res<<endl;
    return 0;
}
/*
// 第一题
int arr[1000009];
int temp[300000];

int main()
{
    int k = 0;
    for (int i = 2; i < 1000009; i++)
    {
        if (arr[i]==0)
        {
            temp[k++] = i;
            for (int j = 2 * i; j < 1000009; j += i)
            {
                arr[j] = 1;
            }
        }
    }
    int n;
    while (cin>>n)
    {
        int res = 1;
        for (int i = 0; temp[i] <= n; i++)
        {
            for (int j = temp[i]; j <= n; j *= temp[i])
            {
                res = max(res, j);
            }
        }
        cout<<2*res<<endl;
    }
    return 0;
}*/


/*
// 第三题
int main(){
    int t;
    cin>>t;
    while(t--){
        int A,B,C;
        cin>>A>>B>>C;
        bool flag =false;
        for(int i=0;i<A && !flag;i++){
            if((B*i +C)%A == 0){
                flag = true;
            }
        }
        if(flag)
            cout<<"YES"<<endl;
        else{
            cout<<"NO"<<endl;
        }
    }
    return 0;
}*/