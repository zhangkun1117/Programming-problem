/*
.活动选择问题
 这是《算法导论》上的例子，也是一个非常经典的问题。有n个需要在同一天使用同一个教室的活动a1,a2,…,an，
 教室同一时刻只能由一个活动使用。每个活动ai都有一个开始时间si和结束时间fi 。一旦被选择后，活动ai就占据半开时间区间[si,fi)
 。如果[si,fi]和[sj,fj]互不重叠，ai和aj两个活动就可以被安排在这一天。该问题就是要安排这些活动使得尽量多的活动能不冲突的举行
 。例如下图所示的活动集合S，其中各项活动按照结束时间单调递增排序。
  i | 1   |2   |3   |4   |5   |6   |7   |8   |9   |10
  si|1    |3   |0   |5   |3   |5   |6   |8   |8   | 2
  fi|4    |5   |6   |7   |8   |9   |10  |11  |12  |13
*/
#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
int N;
struct Act
{
    int start;
    int end;
} act[100010];

bool cmp(Act a, Act b)
{
    return a.end < b.end;
}

int greedy_activity_selector()
{
    int num = 1, i = 1;
    for (int j = 2; j <= N; j++)
    {
        if (act[j].start >= act[i].end)
        {
            i = j;
            num++;
        }
    }
    return num;
}

int main()
{
    int t;
    cin >> t;

    while (t--)
    {
        scanf_s("%d", &N);
        for (int i = 1; i <= N; i++)
        {
            scanf_s("%lld %lld", &act[i].start, &act[i].end);
        }
        act[0].start = -1;
        act[0].end = -1;
        sort(act + 1, act + N + 1, cmp);
        int res = greedy_activity_selector();
        cout << res << endl;
    }
    return 0;
}

/*钱币找零问题
这个问题在我们的日常生活中就更加普遍了。假设1元、2元、5元、10元、20元、50元、100元的纸币分别有c0,
 c1, c2, c3, c4, c5, c6张。现在要用这些钱来支付K元，至少要用多少张纸币？用贪心算法的思想，很显然
 ，每一步尽可能用面值大的纸币即可。在日常生活中我们自然而然也是这么做的。在程序中已经事先将
 Value按照从小到大的顺序排好。
*/

#include<iostream>  
#include<algorithm>  
using namespace std;  
const int N=7;   
int Count[N]={3,0,2,1,0,3,5}; 
int Value[N]={1,2,5,10,20,50,100};  
    
int solve(int money)   
{  
    int num=0;  
    for(int i=N-1;i>=0;i--)   
    {  
        int c=min(money/Value[i],Count[i]);  
        money=money-c*Value[i];  
        num+=c;  
    }  
    if(money>0) num=-1;  
    return num;  
}  
   
int main()   
{  
    int money;  
    cin>>money;  
    int res=solve(money);  
    if(res!=-1) cout<<res<<endl;  
    else cout<<"NO"<<endl;  
}  
/*3.再论背包问题
在从零开始学动态规划中我们已经谈过三种最基本的背包问题：零一背包，部分背包，完全背包。很容易证明，背包问题不能使用贪心算法。
然而我们考虑这样一种背包问题：在选择物品i装入背包时，可以选择物品的一部分，而不一定要全部装入背包。这时便可以使用贪心算法求解了。
计算每种物品的单位重量价值作为贪心选择的依据指标，选择单位重量价值最高的物品，将尽可能多的该物品装入背包，依此策略一直地进行下去，
直到背包装满为止。在零一背包问题中贪心选择之所以不能得到最优解原因是贪心选择无法保证最终能将背包装满，部分闲置的背包空间使每
公斤背包空间的价值降低了。在程序中已经事先将单位重量价值按照从大到小的顺序排好。
*/
#include<iostream>     
using namespace std;     
const int N=4;    
void knapsack(float M,float v[],float w[],float x[]);    
    
int main()    
{    
    float M=50;  
    //背包所能容纳的重量     
    float w[]={0,10,30,20,5};  
    //每种物品的重量    
    float v[]={0,200,400,100,10};    
    //每种物品的价值   
    float x[N+1]={0};    
    //记录结果的数组   
    knapsack(M,v,w,x);    
    cout<<"选择装下的物品比例："<<endl;    
    for(int i=1;i<=N;i++) cout<<"["<<i<<"]:"<<x[i]<<endl;    
}    
    
void knapsack(float M,float v[],float w[],float x[])    
{    
    int i;    
    //物品整件被装下    
    for(i=1;i<=N;i++)  
    {    
        if(w[i]>M) break;     
        x[i]=1;    
        M-=w[i];    
    }     
    //物品部分被装下    
    if(i<=N) x[i]=M/w[i];     
}

/*
 * 4.多机调度问题
n个作业组成的作业集，可由m台相同机器加工处理。要求给出一种作业调度方案，使所给的n个作业在尽可能短的时间内由m台机器加工处理完成。
作业不能拆分成更小的子作业；每个作业均可在任何一台机器上加工处理。这个问题是NP完全问题，还没有有效的解法(求最优解)，但是可以用
贪心选择策略设计出较好的近似算法(求次优解)。当n<=m时，只要将作业时间区间分配给作业即可；当n>m时，首先将n个作业从大到小排序，然
后依此顺序将作业分配给空闲的处理机。也就是说从剩下的作业中，选择需要处理时间最长的，然后依次选择处理时间次长的，直到所有的作业
全部处理完毕，或者机器不能再处理其他作业为止。如果我们每次是将需要处理时间最短的作业分配给空闲的机器，那么可能就会出现其它所有
作业都处理完了只剩所需时间最长的作业在处理的情况，这样势必效率较低。在下面的代码中没有讨论n和m的大小关系，把这两种情况合二为一了
。
 */
#include<iostream>    
#include<algorithm>      
using namespace std;    
int speed[10010];    
int mintime[110];    
  
bool cmp( const int &x,const int &y)    
{    
    return x>y;    
}    
  
int main()    
{    
    int n,m;           
    memset(speed,0,sizeof(speed));    
    memset(mintime,0,sizeof(mintime));    
    cin>>n>>m;    
    for(int i=0;i<n;++i) cin>>speed[i];    
    sort(speed,speed+n,cmp);    
    for(int i=0;i<n;++i)     
    {   
        *min_element(mintime,mintime+m)+=speed[i];     
    }     
    cout<<*max_element(mintime,mintime+m)<<endl;   
} 
/*5.小船过河问题
POJ1700是一道经典的贪心算法例题。题目大意是只有一艘船，能乘2人，船的运行速度为2人中较慢一人的速度，过去后还需一个人把船划回来
，问把n个人运到对岸，最少需要多久。先将所有人过河所需的时间按照升序排序，我们考虑把单独过河所需要时间最多的两个旅行者送到对岸
去，有两种方式：
1.最快的和次快的过河，然后最快的将船划回来；次慢的和最慢的过河，然后次快的将船划回来，所需时间为：t[0]+2*t[1]+t[n-1]；
2.最快的和最慢的过河，然后最快的将船划回来，最快的和次慢的过河，然后最快的将船划回来，所需时间为：2*t[0]+t[n-2]+t[n-1]。
算一下就知道，除此之外的其它情况用的时间一定更多。每次都运送耗时最长的两人而不影响其它人，问题具有贪心子结构的性质。
AC代码：
*/
#include<iostream>  
#include<algorithm>  
using namespace std;  
  
int main()  
{  
    int a[1000],t,n,sum;  
    scanf("%d",&t);  
    while(t--)  
    {  
        scanf("%d",&n);  
        sum=0;  
        for(int i=0;i<n;i++) scanf("%d",&a[i]);  
        while(n>3)  
        {  
            sum=min(sum+a[1]+a[0]+a[n-1]+a[1],sum+a[n-1]+a[0]+a[n-2]+a[0]);  
            n-=2;  
        }  
        if(n==3) sum+=a[0]+a[1]+a[2];  
        else if(n==2) sum+=a[1];  
        else sum+=a[0];  
        printf("%d\n",sum);  
    }  
}  

/*6.区间覆盖问题
POJ1328是一道经典的贪心算法例题。题目大意是假设海岸线是一条无限延伸的直线。陆地在海岸线的一侧，而海洋在另一侧。
每一个小的岛屿是海洋上的一个点。雷达坐落于海岸线上，只能覆盖d距离，所以如果小岛能够被覆盖到的话，它们之间的距离
最多为d。题目要求计算出能够覆盖给出的所有岛屿的最少雷达数目。对于每个小岛，我们可以计算出一个雷达所在位置的区间。
*/
#include<cmath>  
#include<iostream>  
#include<algorithm>  
using namespace std;  
struct Point  
{  
    double x;  
    double y;  
}point[1000];  
  
int cmp(const void *a, const void *b)  
{  
    return (*(Point *)a).x>(*(Point *)b).x?1:-1;  
}  
  
int main()  
{  
    int n,d;  
    int num=1;  
    while(cin>>n>>d)  
    {  
        int counting=1;  
        if(n==0&&d==0) break;  
        for(int i=0;i<n;i++)  
        {  
            int x,y;  
            cin>>x>>y;  
            if(y>d)  
            {  
                counting=-1;  
            }  
            double t=sqrt(d*d-y*y);  
            //转化为最少区间的问题   
            point[i].x=x-t;  
            //区间左端点   
            point[i].y=x+t;  
            //区间右端点   
        }  
        if(counting!=-1)  
        {  
            qsort(point,n,sizeof(point[0]),cmp);  
            //按区间左端点排序   
            double s=point[0].y;  
            //区间右端点   
            for(int i=1;i<n;i++)  
            {  
                if(point[i].x>s)  
                //如果两个区间没有重合,增加雷达数目并更新右端点   
                {  
                    counting++;  
                    s=point[i].y;   
                }  
                else if(point[i].y<s)  
                //如果第二个区间被完全包含于第一个区间,更新右端点   
                {  
                    s=point[i].y;  
                }  
            }  
        }  
        cout<<"Case "<<num<<':'<<' '<<counting<<endl;  
        num++;   
    }  
} 