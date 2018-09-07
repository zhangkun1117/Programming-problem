#include <bits/stdc++.h>
/*
** 实现排列组合的累加，即c(n,1)+c(n,2)+c(n,3)...+c(n,m);
** 从前面一个值递推出后一个值，时间复杂度为o(n);
*/
int Arrage(int n,int m)
{
    if(m==0) return 1;
    if(m==1) return n;
    int ipre=n,isum=n+1;
    for(int i=2;i<m;i++)
    {
        ipre *= (n-i+1)/i;
        isum += ipre;
    }
    return isum;
}
/*
也可以动态规划做，当m>n/2时，C(n,m) = C(n,n-m);
*/
int Arrage(int n,int m)
{
    if(m==0) return 1;
    vector<int> dp(m+1,0);
    dp[0]=1;dp[1]=n;
    for(int i=2;i<=m;i++)
    {
        if(m<n/2)
            dp[i] = dp[i-1]*(n-i+1)/i;
        else
            dp[i] = dp[n-m];
    }
    int isum=0;
    for(int i=0;i<=m;i++)
        isum+=dp[i];
    return isum;
}