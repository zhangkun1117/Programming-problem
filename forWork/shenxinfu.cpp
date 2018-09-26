#include <iostream>
#include <vector>
#include <numeric>
#include <limits>
#include <string.h>   
#include <set>
#include <algorithm>
#include <map>

using namespace std;
int main(){

    int T;
    while(T--){
        long long int a1,b1,v1,a2,b2,v2;
        cin>>a1>>b1>>v1>>a2>>b2>>v2;
        long long int x=0,y=0;
        if(a1!=0 && a2 !=0){
            if((v1*a2 - a1*v2)%(b1*a2 - a2*b1) !=0){
                cout<<"UBKNOWN"<<endl;
            }else{
                y = (v1*a2 - a1*v2)/(b1*a2 - a2*b1);
                x = (v1/a1 - b1*y/a1);
                cout<<x<<" "<<y<<endl;
            }
        }else{
            if(a1 ==0 && a2 !=0 && b1 !=0 && v1%b1 ==0){
                y = v1/b1;
                x= (v2-b2*y)/a2;
                cout<<x<<" "<<y<<endl;
            }else if(a2 ==0 && a1 !=0 && b2 !=0 && v2%b2 ==0){
                y = v2/b2;
                x= (v1-b1*y)/a1;
                cout<<x<<" "<<y<<endl;
            }
            else{
                cout<<"UBKNOWN"<<endl;
            }
        }
    }
    return 0;
}
/*
int main(){
    int T;
    cin>>T;
    while(T--){
        int n;
        cin>>n;
        vector<int> arr(n);
        for(int i=0;i<n;i++){
            cin>>arr[i];
        }
        if(arr[0]<arr[n-1]){
            reverse(arr.begin(),arr.end());
        }
        int sum=0;
        for(int i=1,j=0;i<n;i++){
            if(arr[i] >= arr[j]){
                sum += min(arr[j],arr[i])*(j-i);
                j=i;  
            }else{
                int pos = max_element(arr.begin()+j,arr.end()) - arr.begin()-j;
                sum += min(arr[j],arr[pos]) *(pos-j);
                j = pos;
                i = pos;
            }
        }
        cout<<sum<<endl;
    }
    return 0;
}*/