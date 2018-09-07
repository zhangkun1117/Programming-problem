//参见博客：https://blog.csdn.net/qq_32400847/article/details/51474105


/*
3. 有一批共n个集装箱要装上2艘载重量分别为c1和c2的船，其中集装箱i的重量为wi，且。装载问题要求确定是否有一个合理的装载方案可
将这些集装箱装上这2艘船。如果有，找出一种装载方案。例如当n=3，c1=c2=50且w=[10,40,40]时，则可以将集装箱1和2装到第一艘轮船
上，而将集装箱3装到第二艘轮船上；如果w=[20,40,40]，则无法将这3个集装箱都装上轮船。容易证明，如果一个给定装载问题有解，则
首先将第一艘船尽可能装满再将剩余的集装箱装上第二艘船可得到最优装载方案。将第一艘船尽可能装满等价于选取全体集装箱的一个子集
，使该子集中集装箱重量之和最接近c1。用回溯法解装载问题,  时间复杂度O(2^n)，在某些情况下优于动态规划算法。剪枝方案是如果
当前已经选择的全部物品载重量cw+剩余集装箱的重量r<=当前已知的最优载重量bestw，则删去该分支。*/
#include<iostream>  
using namespace std;    
int n;//集装箱数    
int w[40];//集装箱重量  
int c1,c2;//两艘船的载重量    
int ans;//当前载重量    
int bestans;//当前最优载重量    
int r;//剩余集装箱重量    
    
void backtrack(int i)    
{          
    if(i>n)      
    {    
        if(ans>bestans) bestans=ans;    
            return;    
    }    
    r-=w[i];    
    if(ans+w[i]<=c1)    
    {     
      ans+=w[i];    
      backtrack(i+1);    
      //改回辅助的全局变量   
      ans-=w[i];    
    }    
    if(ans+r>bestans) backtrack(i+1);      
    //改回辅助的全局变量   
    r+=w[i];    
}      
    
int maxloading()    
{    
    ans=0;    
    bestans=0;    
    backtrack(1);     
    return bestans;    
}  
  
int main()    
{      
    cin>>n>>c1>>c2;    
    int i=1;    
    int sum=0;    
    //集装箱总重量   
    while(i<=n)    
    {    
        cin>>w[i];    
        r+=w[i];    
        sum+=w[i];    
        i++;    
    }      
    maxloading();    
    if(bestans>0&&((sum-bestans)<=c2)) cout<<bestans<<endl;    
    else if(sum<=c2) cout<<bestans<<endl;    
    else cout<<"No"<<endl;    
}
/*
4.批处理作业调度问题

给定n个作业的集合{J1,J2,…,Jn}。每个作业必须先由机器1处理，然后由机器2处理。作业Ji需(1≤i≤n)要机器j(1≤j≤2)的处理时间为tji。
对于一个确定的作业调度，设Fji是作业i在机器j上完成处理的时间。所有作业在机器2上完成处理的时间和称为该作业调度的完成时间和：
。要求对于给定的n个作业，制定最佳作业调度方案，使其完成时间和达到最小。

|  tji          |机器1         |机器2          |
|  作业1        |2             |1              |
|  作业2        |3             |1              |
|  作业2        |3             |3              | 

由于机器有两个，每个作业必须从机器1处理，再到机器2处理，所以会两个作业同时处理，例如对上面的表格按照（1,2,3）的顺序调度： 
(括号内代表作业序号)

 机器1     机器2 
  2(1) 
  3(2)      1(1) 
  2(3)      1(2) 
            3(3)

每一个作业的处理时间 = 机器2的处理时间 + 机器2等待处理的时间（包括了之前作业的时间 和 本作业在机器1处理的时间） 
所以我们求作业的处理时间，就是求该作业从开始到机器2处理完的时间：

作业1的处理时间：2+1 = 3 
作业2的处理时间：2 + 3 + 1 = 6 （作业1的在机器1的处理时间，作业2的在机器1的处理时间 和 作业1在机器2的处理时间的较大时间（因为两者是同时进行的），作业2在机器2的处理时间） 
作业3的处理时间：2 + 3 + 2 + 3 = 10

所以（1,2,3）顺序的作业调度得到的作业调度时间为19

#define MAX 200  
#include<iostream>  
using namespace std;  
int* x1;//作业Ji在机器1上的工作时间  
int* x2;//作业Ji在机器2上的工作时间  
int number=0;//作业的数目  
int* xorder;//作业顺序  
int* bestorder;//最优的作业顺序  
int bestvalue=MAX;//最优的时间  
int xvalue=0;//当前完成用的时间  
int f1=0;//机器1完成的时间  
int* f2;//机器2完成的时间  
  
void backtrack(int k)  
{  
    if(k>number)  
    {  
        for(int i=1;i<=number;i++) bestorder[i]=xorder[i];  
        bestvalue=xvalue;  
    }  
    else  
    {  
        for(int i=k;i<=number;i++)  
        {  
           f1+=x1[xorder[i]];  
           f2[k]=(f2[k-1]>f1?f2[k-1]:f1)+x2[xorder[i]];  
           xvalue+=f2[k];  
           swap(xorder[i],xorder[k]);  
           if(xvalue<bestvalue) backtrack(k+1);  
           swap(xorder[i],xorder[k]);  
           xvalue-=f2[k];  
           f1-=x1[xorder[i]];  
        }  
    }  
}  
  
int main()  
{  
    cout<<"请输入作业数目：";  
    cin>>number;  
    x1=new int[number+1];  
    x2=new int[number+1];  
    xorder=new int[number+1];  
    bestorder=new int[number+1];  
    f2=new int[number+1];  
    x1[0]=0;  
    x2[0]=0;  
    xorder[0]=0;  
    bestorder[0]=0;  
    f2[0]=0;  
    cout<<"请输入每个作业在机器1上所用的时间："<<endl;  
    int i;  
    for(i=1;i<=number;i++)  
    {  
        cout<<"第"<<i<<"个作业=";  
        cin>>x1[i];  
    }  
    cout<<"请输入每个作业在机器2上所用的时间："<<endl;  
    for(i=1;i<=number;i++)  
    {  
        cout<<"第"<<i<<"个作业=";  
        cin>>x2[i];  
    }  
    for(i=1;i<=number;i++) xorder[i]=i;     
    backtrack(1);  
    cout<<"最节省的时间为："<<bestvalue<<endl;  
    cout<<"对应的方案为：";  
    for(i=1;i<=number;i++) cout<<bestorder[i]<<"  ";  

    cout<<endl;  
    return 0;
} */
