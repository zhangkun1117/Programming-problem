/*
一只兔子藏身于20个圆形排列的洞中（洞从1开始编号），一只狼从x号洞开始找,下次隔一个洞找(即在x＋2号洞找)，在下次个两个洞找(即在x＋5号洞找)，它找了n次仍然没有找到。问兔子可能在那些洞中。
输入描述:
输入有多组数据，每组数据一行两个整数分别为x和n(x <= 20,n <= 100000)
输出描述:
每组数据一行按从小到大的顺序输出兔子可能在的洞，数字之间用空格隔开。若每个洞都不肯能藏着兔子，输出-1。
*/
#include <bits/stdc++.h>
using namespace std;
#define num_hole 20
int main(){
    int x,n;
    while(cin>>x>>n)
    {
        vector<bool> arr(num_hole+1,false);
        arr[x] = true;
        for(int i=1;i<=n;i++)
        {
            x = (x+i+1)%20;
            arr[x] =true;
        }
        arr[20] = arr[0];//求mod 操作会将20位置的值放置到0的位置。
        int count=0;
        for(int i=1;i<=num_hole;i++)
            if(arr[i] == false)
            {
                cout<<i<<" ";
                count++;
            }
        
        if(count==0)
            cout<<-1;
        cout<<endl;        
    }
    return 0;
}