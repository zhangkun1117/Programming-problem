/*最大公约数和最小公倍数，存在连个数，m和n。
* multi = m*n;
* 则最小公倍数为两者乘积除以最大公约数
*/
//最大公约数递归版
int gcd(int a,int b)
{  
    //a>b  
    if (b==0)         
        return a;    
    return gcd(b, a%b);
}
// 最大公约数非递归版
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
