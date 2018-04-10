/*
题目描述
A、B和C。如果C包含且仅包含来自A和B的所有字符，而且在C中属于A的字符之间保持原来在A中的顺序，属于B的字符之间保持原来在B中的顺序，那么称C是A和B的混编。实现一个函数，判断C是否是A和B的混编。

给定三个字符串A,B和C，及他们的长度。请返回一个bool值，代表C是否是A和B的混编。保证三个串的长度均小于等于100。

测试样例：
"ABC",3,"12C",3,"A12BCC",6
返回：true
*/
//动态规划转为查找公共字符串
class Mixture {
public:
    //如果A和C的公共字符串为A，则A肯定为
    bool common_string(string A,int n,string B,int m)
    {
        vector<vector<int> > dp(n+1,vector<int>(m+1,0));
        for(int i=1;i<=n;i++)
            for(int j=1;j<=m;j++)
                if(A[i] == B[j])
                    dp[i][j] =dp[i-1][j-1]+1;
                else
                    dp[i][j] = max(dp[i-1][j],dp[i][j-1]);
        if(dp[n][m] == n)
            return true;
        return false;
    }
    bool chkMixture(string A, int n, string B, int m, string C, int v) {
        // write code here
        if(n>v || m>v)
            return false;
        return common_string(A,n,C,v) && common_string(B,m,C,v);
    }
    
};