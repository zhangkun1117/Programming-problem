#include <iostream>
#include <vector>
#include <numeric>
#include <limits>
#include <string.h>   
#include <set>
#include <algorithm>
#include <map>
#include <deque>

using namespace std;

int main(){
    int N;
    deque<int> que(N);
    while(N--){
        int temp;
        cin>>temp;
        que.push_back(temp);
    }
    int x=0,y=0,z=0;
    while(1){
        if(!que.empty() && que.front() >= que.back()){
            x += que.front();
            que.pop_front();
        }else if(!que.empty() && que.front() < que.back()){
            x += que.back();
            que.pop_back();
        }
        if(!que.empty() && que.front() >= que.back()){
            y += que.front();
            que.pop_front();
        }else if(!que.empty() && que.front() < que.back()){
            y += que.back();
            que.pop_back();
        }
        if(!que.empty() && que.front() >= que.back()){
            z += que.front();
            que.pop_front();
        }else if(!que.empty() && que.front() < que.back()){
            z += que.back();
            que.pop_back();
        }
        if(que.empty()){
            break;
        }
    }
    cout<<x<<endl;
    return 0;
}
/*
struct node{
    int x;
    int y;
};
bool compare(node n1,node n2){
    if(n1.x < n2.x)
        return true;
    else if(n1.x == n2.x){
        return n1.y < n2.y;
    }
    return false;
}

node getzuobiao(node n1,node n2,node n3){
    node n4;
    n4.x = n1.x + n3.x - n2.x;
    n4.y = n1.y + n3.y - n2.y;
    return n4;
}
bool getOrder(node n1,node n2,node n3,node &n4){
    if((n1.x - n2.x)*(n2.x - n3.x) + (n1.y - n2.y)*(n2.y-n3.y) ==0){
        n4 = getzuobiao(n1,n2,n3);
        return true;
    }
    if((n1.x - n3.x)*(n2.x - n3.x) + (n1.y - n3.y)*(n2.y-n3.y) ==0){
        n4 = getzuobiao(n1,n3,n2);
        return true;
    }
    if((n1.x - n3.x)*(n2.x - n1.x) + (n1.y - n3.y)*(n2.y-n1.y) ==0){
        n4 = getzuobiao(n3,n2,n1);
        return true;
    }
    return  false;
}
int countChang(vector<node> &array){
    int count=0;
    int N = array.size();
    for(int i=0;i<N-2;i++){
        for(int j=i+1;j<N-1;j++){
            for(int k = j+1;j<N;j++){
                node n4 ;
                if(getOrder(array[i],array[j],array[k],n4)){
                     array.push_back(n4);
                     count++;
                     return count;
                }
            }
        }
    }
    return count;
}
int main(){
    int N;
    cin>>N;
    vector<node> arr(N);
    for(int i=0;i<N;i++){
        cin>>arr[i].x>>arr[i].y;
    }
    while(countChang(arr) != 0){};
    
    cout<<arr.size()<<endl;
    return 0;
}*/