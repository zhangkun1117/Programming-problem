/*
经典gcd问题。通过10%
*/
#include<iostream>
#include<cmath>
using namespace std;
int gcd(int m, int n)
{
    if (m == 0)
        return n;
    if (n == 0)
        return m;
    if (m < n)
    {
        int tmp = m;
        m = n;
        n = tmp;
    }
    while (n != 0)
    {
        int tmp = m % n;
        m = n;
        n = tmp;
    }
     return m;
}

int main()
{
    int N,n,m,p;
    while(cin>>N>>n>>m>>p)
    {
        vector<int> A(N+1,0);
        A[1] =p;
        for(int i=2;i<=N;i++)
            A[i] = (A[i-1] + 153)%p;
        //根据A
        int sum=0;
        for(int i=1;i<=n;i++)
            for(int j=1;j<=m;j++)
                sum+= A[gcd(n,m)];
        cout<<sum<<endl;
    }
    return 0;
}
/*
给出一个数，求从1~n组成一个数的位数:
输入4 
组成数1234 
输出 4 
*/
//通过40%
#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;
int leng(long  a)//求所给数位数
{
    int flag=0;
    int b = a;
    while(b)
    {
    b/=10;
    flag++;
    }
 return flag;
} 
int bits(int n)//
 {
 	int bit = leng(n);
 	int sum;
 	if(n<10)
 	    return n;
 	sum = 9;
 	for(int i=1;i<bit-1;i++)
 	    sum += 9*pow(10,bit-1);
 	sum+= n-pow(10,bit-1)+1;
 	return sum;
 }
int main()
{
    int n;
    while(cin>>n)
    {
        int num;
        for(int i=0;i<n;i++)
        {
            cin>>num;
        	cout<<bits(num)<<endl;
        }
    }
    return 0;
}