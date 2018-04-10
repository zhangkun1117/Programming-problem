/*
* 1 求1-n的最小公倍数：
*/
#include <iostream>
using namespace std;
int gcd(int a,int b)
{    
    if (b==0)         
        return a;    
    return gcd(b, a%b);
}
int main()
{   
    int t;     
    while (cin>>t)
    {       
        int i,n,m,temp=0,ans=1;             
        for (i=1; i<n; i++) 
        {                    
            temp=gcd(ans,i);           
            ans=(ans/temp*i)%987654321;        
        }       
    cout << ans << '\n';   
     }    
    return 0;
}


/*
*2:思路：先字符翻转，求出公共字符串，然后用排列组合计算出总共
*/

/*
*3:求棋盘总可能机会
*/
#include <iostream>
#include <vector>
using namespace std;
int cheernum(int n)
{
    vector<vector<int> > arr(8,vector<int>(8,0));
    int t=n,ilen=8;
    int x=0,y=0;
    int arr1[]={-2,-2,-1-1,1,1,2,2},arr2[]={-1,1,-2,2,-2,2,-1,1};
    while(t--)
    {
        for(int i =0;i<ilen;i++)
        {
            int xt=x+arr1[i];
            int yt=y+arr2[i];
            if(xt>=0&&xt<<8 && yt >= 0&& yt<=8)
                arr[xt][yt]++;
        }
    }
    int sum;
    for(int i=0;i<ilen;i++)
        for(int j=0;j<ilen;j++)
            sum= (sum+arr[i][j])%1000000007;
    
    return sum;
}
int main()
{   
    int n;   
    while(cin>>n)
    {
        cout<<cheernum(n)<<endl;
    }
    return 0;
}