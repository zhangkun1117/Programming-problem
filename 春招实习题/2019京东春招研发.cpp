/*
* 1 求1-n的最小公倍数：
*  其他解法： 求解所有数的质因数，然后算乘积
*/
//按两两找最小公倍数
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
        int i,n,m;
        long long temp=0;
        long long ans=1;             
        for (i=1; i<n; i++) 
        {                    
            temp=gcd(ans,i);           
            ans=(ans/temp*i)%987654321;        
        }       
    cout << ans << '\n';   
     }    
    return 0;
}

//按寻找质因数1-n
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define mod 987654321
#define maxn 100010
bool vis[maxn];
ll Pow(int x,int n){
    ll ans=1;
    while(n){
        if(n&1) ans=ans*x%mod;
        x=x*x%mod;
        n>>=1;
    }
    return ans;
}
int p[maxn],len=0;
void init(){
    for(int i=2;i<maxn;i++){
        if(vis[i]) continue;
        for(int j=2*i;j<maxn;j+=i)
            vis[j]=true;
    }
    for(int i=2;i<maxn;i++)
        if(!vis[i]) p[len++]=i;
}
int num[maxn];
int main(){
    init();
    int n,t;
    scanf("%d",&n);
    for(int i=2;i<=n;i++){
        t=i;
        for(int j=0;p[j]*p[j]<=t;j++){
            int cnt=0;
            while(t%p[j]==0){
                t/=p[j];cnt++;
            }
            num[p[j]]=max(num[p[j]],cnt);
        }
        if(t>1) num[t]=max(num[t],1);
    }
    ll ans=1;
    for(int i=2;i<maxn;i++){
        ans=ans*Pow(i,num[i])%mod;
    }
    printf("%lld\n",ans);
    return 0;
}


/*
*2: 同回文串的个数解法
*思路：参考牛客网：https://www.nowcoder.com/discuss/72838
*/

//解法一：
#include<bits/stdc++.h>
using namespace std;
long long dp[55][55];
char s[55];
int main(){
    char s[55];
    while(scanf("%s",s))
    {   
        int n=strlen(s);
        for(int i=0;i<n;i++)
        for(int j=0;j<=i;j++){
            if(i==j) dp[i][j]=2;
            else dp[i][j]=1;
        }
        for(int l=2;l<=n;l++){
            for(int i=0;i+l-1<n;i++){
                int j=i+l-1;
                dp[i][j]=dp[i+1][j]+dp[i][j-1];
            if(s[i]!=s[j]) dp[i][j]-=dp[i+1][j-1];
        }
        }
    printf("%lld\n",dp[0][n-1]-1);
    }
    return 0;
}
//解法二：思路同求有多少个回文串 https://blog.csdn.net/nwpu_yike/article/details/20871141
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