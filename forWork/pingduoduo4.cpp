#include <bits/stdc++.h>
using namespace std;

int main(){
    int n,m;
    while(cin>>n>>m){
        vector<int> arr(m);
        map<int,int,greater<int>> map;
        for(int i=0;i<m;i++){
            cin>>arr[i];
        } 
        for(int i=0;i<n;i++){
           int temp;
           cin>>temp;
           cin>>map[temp];
        }
        for(auto it = map.begin();it!= map.end();it++){
            sort(arr.begin(),arr.end());
            int temp = it->second;
            for(int i=m-1;i>=0;i--){
              //  cout<<temp<<" "<<arr[i]<<endl;
                if(temp >= arr[i]){
                    temp = temp - arr[i];
                    arr[i] =0;
                }
             //   cout<<temp<<" "<<arr[i]<<endl;
                if(temp<arr[0]){
                    it->second = temp;
                    break;
                }
            }
            cout<<temp<<endl;
        }
     
    }
}
/*//第四题
int main(){
    int n;
    while(cin>>n){
        vector<int>  arr(n);
        if(n<3)
            cout<<"0"<<endl;
        for(int i=0;i<n;i++){
            cin>>arr[i];
        }
        int n1=0,n2=0,n3=0,m1=0,m2=0;
        if(arr[0]>0)
            n1=arr[0];
        else
            m1 =arr[0];
        for(int i=1;i<n;i++){
            if(arr[i]>0){
                if(arr[i]>n1){
                    n3 = n2;
                    n2 = n1;
                    n1 = arr[i];
                }
                else if(arr[i]>n2&&arr[i]<n1){
                    n3 = n2;
                    n2 =arr[i];    
                }
                else if(arr[i]>n3 && arr[i]<n2){
                    n3 = arr[i];
                }
            }
            else{
                if(arr[i]<m1){
                    m2 = m1;
                    m1 = arr[i];
                }
                else if( arr[i]<m1 && arr[i]>m2){
                    m2 =arr[i];
                }
            }
        }
        int res = (n2*n3 > m1*m2)?(n1*n2*n3):(n1*m1*m2);
        cout<<res<<endl;       
    }
}*/
/*
#include <bits/stdc++.h>
using namespace std;

int main(){
    int n;
    while(cin>>n){
        vector<pair<int,int> > arr(n);
        for(int i=0;i<n;i++){
            cin>>arr[i].first>>arr[i].second;
        }
        int count =0;
        for(int i=0;i<n-2;i++){
            for(int j=i+1;j<n-1;j++){
                int a = sqrt(pow(arr[i].first - arr[j].first,2)+pow(arr[i].second-arr[j].second,2));
                for(int k = j+1;k<n;k++){
                    int b = sqrt(pow(arr[i].first - arr[k].first,2)+pow(arr[i].second-arr[k].second,2));
                    int c = sqrt(pow(arr[k].first - arr[j].first,2)+pow(arr[k].second-arr[j].second,2));
                    if((a+b>c) && (a+c>b) && (b+c>a))
                        count++;
                }
            }
        }
        cout<<count<<endl;
    }
}*/