#include <iostream>
#include <vector>
#include <numeric>
#include <limits>
#include <string>   
#include <set>
#include <algorithm>
#include <map>
#include <stdio.h>
#include <string.h>
using namespace std;
// 黑积木问题
int main(){    
    int x,y;    
    while(cin>>x>>y){    
        int maxx = INT_MIN;    
        int num = 0;    
        for(int i = 0;i<=7;i++){    
            int temp = x*i+y*(7-i);    
            if(temp>=maxx&&temp<0){
                maxx = temp;  num = i;
            }    
        }    
        cout<<maxx*2+x*(num>=3?3:num)+y*(num>=3?0:3-num)<<endl;
    }
    system("pause");
    return 0;
}

/*//素勾股数
int res(int a,int b){
    int x = a>b?a:b;
    int y = a<=b?a:b;
    while(x%y!=0){
        int temp = y;
        y = x%y;
    x = temp;
    }
    return y;
}
struct pt{
    int x;
    int y;
    int z;
    pt(int a,int b,int c):x(a),y(b),z(c){}
    pt();
};
int main(){
    int n;
    while(cin>>n){
    vector<pt> vec;
    int count = 0;
    for(int i = 1;i<=n;i++){
        for(int j = i;j<=n;j++){
            int c = sqrt((double)i*i+j*j);
            if(c*c == i*i+j*j&&c<=n){
                int d = res(i,j);
                pt p(i/d,j/d,c/d);
                bool flg = true;
                for(int i = 0;i<vec.size();i++){
                    if(vec[i].x==p.x&&vec[i].y==p.y&&vec[i].z==p.z){
                    flg = false;
                    break;
                }
            }
            if(flg&&res(i/d,j/d)==1&&res(i/d,c/d)==1&&res(j/d,c/d)==1){
                count++;
                vec.push_back(p);
            }
            }
        }
    }
    cout<<count<<endl;
    }
return 0;
}