#include <iostream>
#include  <set>
#include  <vector>
using namespace std;

vector<int> arrayPrint(vector<vector<int> > arr, int n) {
    // write code here
    int num =2*n-1;
    vector<int> res(n*n,0);
    int x,y;
    while(num>0)
    {
             if(num>=n)
             {
                 x = 0;y =num-n;
             } 
             else{
                 x = n-num;y = 0;
             }
            while(x>=0 && x<n && y>=0 && y<n){
                res.push_back(arr[x++][y++]);
            cout<<arr[x-1][y-1]<< " ";
            }
        num--;
    }
        return res;
    }
int main()
{
    int n=4;
    vector<vector<int> > arr(n,vector<int>(n,0));
    int a=1;
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            arr[i][j] = a++;
    
    vector<int> res;
    res = arrayPrint(arr,n);
    return 0;
}