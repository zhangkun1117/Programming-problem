/*度度熊想去商场买一顶帽子，商场里有N顶帽子，有些帽子的价格可能相同。度度熊想买一顶价格第三便宜的帽子，问第三便宜的帽子价格是多少？ 
输入描述:
首先输入一个正整数N（N <= 50），接下来输入N个数表示每顶帽子的价格（价格均是正整数，且小于等于1000）


输出描述:
如果存在第三便宜的帽子，请输出这个价格是多少，否则输出-1

输入例子1:
10
10 10 10 10 20 20 30 30 40 40

输出例子1:
30
*/
#include <bits/stdc++.h>
using namespace std;

int result(vector<int> a,int n)
{
    set<int> arr;
    for(int i=0;i<n;i++)
        arr.insert(arr.begin(),a[i]);
    int ilen = arr.size();
    if(ilen<3)
        return -1;
    auto it =arr.begin();
    for(int i=0;it != arr.end()&& i<2;i++,it++);
    return *it;
}

int main()
{
    int n;
    while(cin>>n)
    {
        vector<int> arr(n);
        for(int i=0;i<n;i++)
            cin>>arr[i];
        cout<<result(arr,n)<<endl;
    }
        return 0;
}
/*
一个数轴上共有N个点，第一个点的坐标是度度熊现在位置，第N-1个点是度度熊的家。现在他需要依次的从0号坐标走到N-1号坐标。
但是除了0号坐标和N-1号坐标，他可以在其余的N-2个坐标中选出一个点，并直接将这个点忽略掉，问度度熊回家至少走多少距离？ 
输入描述:
输入一个正整数N, N <= 50。

接下来N个整数表示坐标，正数表示X轴的正方向，负数表示X轴的负方向。绝对值小于等于100


输出描述:
输出一个整数表示度度熊最少需要走的距离。

输入例子1:
4
1 4 -1 3

输出例子1:
4*/
#include <bits/stdc++.h>
using namespace std;


int result(vector<int> a,int n)
{
    int res = 100000;
    for(int i=1;i<n-1;i++)
    {
        int dis=0;
        for(int j = 1;j<n;j++)
        {
            if(j==i)
            {
                dis =dis +abs(a[j+1]-a[j-1]);
                j++;
            }
            else 
            {
                dis += abs(a[j]- a[j-1]);
            }
        }
        res = min(res,dis);
    }
    return res;
}
int main()
{
    int n;
    while(cin>>n)
    {
        vector<int> arr(n);
        for(int i=0;i<n;i++)
            cin>>arr[i];
        cout<<result(arr,n)<<endl;
    }
        return 0;
}
/*
三维空间中有N个点，每个点可能是三种颜色的其中之一，三种颜色分别是红绿蓝，分别用'R', 'G', 'B'表示。 
现在要找出三个点，并组成一个三角形，使得这个三角形的面积最大。
但是三角形必须满足：三个点的颜色要么全部相同，要么全部不同。 
输入描述:
首先输入一个正整数N三维坐标系内的点的个数.(N <= 50) 

接下来N行，每一行输入 c x y z，c为'R', 'G', 'B' 的其中一个。x，y，z是该点的坐标。(坐标均是0到999之间的整数)


输出描述:
输出一个数表示最大的三角形面积，保留5位小数。

输入例子1:
5
R 0 0 0
R 0 4 0
R 0 0 3
G 92 14 7
G 12 16 8

输出例子1:
6.00000
*/
#include <bits/stdc++.h>
using namespace std;

bool istri(int a,int b,int c)
{
    if(a + b > c && a + c > b && b + c > a)
        return true;
    return false;
}
float area(int a,int b,int c)
{
    float p=(a+b+c)/2.0;            //计算半周长
    float s=sqrt(p*(p-a)*(p-b)*(p-c));        //计算面积
    return s;
}
float area

int main()
{
    vector<vector<int> > arrR = 
    {0,0,0;
     0,4,0;
     0,0,3
    };
    vector<vector<int> > arrG = 
    {92,14,7;
     12,16,8;
    };
    vector<vector<int> > arrB;
    
    float areamin = 100000;
    int ilenR = arrR[0].size();
    int ilenG = arrG[0].size();
    int ilenB = arrB[0].size();
    
    if(ilenR >0 && ilenG >0 && ilenB >0)
    {
        for(int i=0;i<ilenR;i++)
            for(int j=0;j<ilenG;j++)
                for(int k=0;k<ilenB;k++)
                {
                    int a = sqrt(pow(arrR[i][0] - arrG[j][0],2) +pow(arrR[i][1] - arrG[j][1],2) pow(arrR[i][2] - arrG[j][2],2);
                    int b = sqrt(pow(arrR[i][0] - arrB[j][0],2) +pow(arrR[i][1] - arrB[j][1],2) pow(arrR[i][2] - arrB[j][2],2);
                    int c = sqrt(pow(arrG[i][0] - arrB[j][0],2) +pow(arrG[i][1] - arrB[j][1],2) pow(arrG[i][2] - arrB[j][2],2);
                    if(istri(a,b,c))
                        areamin = min(areamin,area(a,b,c));
                }
    }
    else
    {
        if(ilenR >=3)
            for(int i=0;i<ilenR-2;i++)
                for(int j=i;j<ilenR-1;j++)
                    for(int k=0;k<ilenR;k++)
                    {
                        int a = sqrt(pow(arrR[i][0] - arrR[j][0],2) +pow(arrR[i][1] - arrR[j][1],2) pow(arrR[i][2] - arrR[j][2],2);
                        int b = sqrt(pow(arrR[i][0] - arrR[j][0],2) +pow(arrR[i][1] - arrR[j][1],2) pow(arrR[i][2] - arrR[j][2],2);
                        int c = sqrt(pow(arrR[i][0] - arrR[j][0],2) +pow(arrR[i][1] - arrR[j][1],2) pow(arrR[i][2] - arrR[j][2],2);
                        if(istri(a,b,c))
                            areamin = min(areamin,area(a,b,c));
                    }
        if(ilenG >=3)
            for(int i=0;i<ilenG-2;i++)
                for(int j=i;j<ilenG-1;j++)
                    for(int k=0;k<ilenG;k++)
                    {
                        int a = sqrt(pow(arrG[i][0] - arrG[j][0],2) +pow(arrG[i][1] - arrG[j][1],2) pow(arrG[i][2] - arrG[j][2],2);
                        int b = sqrt(pow(arrG[i][0] - arrG[j][0],2) +pow(arrG[i][1] - arrG[j][1],2) pow(arrG[i][2] - arrG[j][2],2);
                        int c = sqrt(pow(arrG[i][0] - arrG[j][0],2) +pow(arrG[i][1] - arrG[j][1],2) pow(arrG[i][2] - arrG[j][2],2);
                        if(istri(a,b,c))
                            areamin = min(areamin,area(a,b,c));
                    }
        if(ilenB >=3)
            for(int i=0;i<ilenB-2;i++)
                for(int j=i;j<ilenB-1;j++)
                    for(int k=0;k<ilenB;k++)
                    {
                        int a = sqrt(pow(arrB[i][0] - arrB[j][0],2) +pow(arrB[i][1] - arrB[j][1],2) pow(arrB[i][2] - arrB[j][2],2);
                        int b = sqrt(pow(arrB[i][0] - arrB[j][0],2) +pow(arrB[i][1] - arrB[j][1],2) pow(arrB[i][2] - arrB[j][2],2);
                        int c = sqrt(pow(arrB[i][0] - arrB[j][0],2) +pow(arrB[i][1] - arrB[j][1],2) pow(arrB[i][2] - arrB[j][2],2);
                        if(istri(a,b,c))
                            areamin = min(areamin,area(a,b,c));
                    }
    }
    cout<<areamin<<endl;
    return 0;
}

/*
度度熊有一个N个数的数组，他想将数组从小到大 排好序，但是萌萌的度度熊只会下面这个操作：
任取数组中的一个数然后将它放置在数组的最后一个位置。
问最少操作多少次可以使得数组从小到大有序？ 
输入描述:
首先输入一个正整数N，接下来的一行输入N个整数。(N <= 50, 每个数的绝对值小于等于1000)


输出描述:
输出一个整数表示最少的操作次数。

输入例子1:
4
19 7 8 25

输出例子1:
2
*/
#include <bits/stdc++.h>
using namespace std;

int result(vector<int> a,int n)
{
    vector<int> temp(a);
    sort(temp.begin(),temp.end());//转换为最长一致性子串
    int count =0;
    for(int i=0,j=0;i<n&& j<n;)
    {   
        if(temp[i]<a[i])
        {
            count++;
            j++;
        }
        else {
            i++;
            j++;
        }
    }
    return count;
}

int main()
{
    int n;
    while(cin>>n)
    {
        vector<int> arr(n);
        for(int i=0;i<n;i++)
            cin>>arr[i];
        cout<<result(arr,n)<<endl;
    }
        return 0;
}
/*
度度熊最近对全排列特别感兴趣,对于1到n的一个排列,度度熊发现可以在中间根据大小关系插入合适的大于和小于符号(即 '>' 和 '<' )使其成为一个合法的不等式数列。但是现在度度熊手中只有k个小于符号即('<'')和n-k-1个大于符号(即'>'),度度熊想知道对于1至n任意的排列中有多少个排列可以使用这些符号使其为合法的不等式数列。 
输入描述:
输入包括一行,包含两个整数n和k(k < n ≤ 1000)


输出描述:
输出满足条件的排列数,答案对2017取模。

输入例子1:
5 2

输出例子1:
66
*/
#include<bits/stdc++.h>
using namespace std;
int n,k,a[1001][1001];
int main(){
    scanf("%d%d", &n, &k);
    k = n-1-k;
    a[0][0] = 1;
    for(int i=1;i<=n;i++){
        a[i][0] = 1;
        for(int j=1;j<=k and j < i;j++){
            a[i][j] = (a[i-1][j] * (j+1) + a[i-1][j-1] * (i-j)) % 2017;
        }
    }
    printf("%d\n",a[n][k]);
}