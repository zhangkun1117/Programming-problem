#include <bits/stdc++.h>
using namespace std;

int main()
{
    int arr[] ={3,4,2,1,3,1};
    int n = 6;
    vector<int> tmp(n,0);

    for(int i=0;i<n;i++)
    {
        for(int j=1;j<= arr[i];j++)
        {
            if(tmp[i+j] == 0)
                tmp[i+j] = tmp[i] + 1; 
        }
    }
    
    cout<<tmp[n-1]<<endl;
    return 0;

}