#include <iostream>
#include <vector>
#include <numeric>
#include <limits>
#include <string>   
#include <set>
#include <list>
#include <algorithm>

using namespace std;

//3 50
struct Result{
    int k;
    int v;
    Result(int k,int v){
        this->k= k;
        this->v =v;
    }
};
int main(){
    int n,m;
    cin>>n>>m;
    vector<long> contain(n);
    vector<long> result(n,0);
    for(int i=0;i<n;i++){
        cin>>contain[i];
    }
    list<Result> results;
    for(int i=0;i<m;i++){
        int a;
        cin>>a;
        if(a==2){
            long layer,vol;
            cin>>layer>>vol;
            long surplus = vol;
            long index = layer;
            long inResult = layer-1;
            while(inResult<layer && surplus>0){
                while(inResult<layer && result[inResult] == contain[index]){
                    inResult++;
                }
                if(surplus>=(contain[inResult] - result[inResult])){
                    result[inResult] = surplus + result[inResult];
                }else{
                    result[inResult] = surplus + result[inResult];
                }
                surplus -= contain[index]-result[inResult];
                inResult++;
            }
        }else if(a ==1){
            int ans;
            cin>>ans;
            //cout<<result[ans-1]<<endl;
            Result re = Result(ans,result[ans-1]);
            results.push_back(re);
        }
        for(int i=0;i<results.size();i++){
            Result res = results.front();
            cout<<res.v<<endl;
            results.pop_front();
        }
    }
    return 0;
}
/*
int main(int argc, char **argv)
{
    int n;
    while(cin>>n){
        vector<int> arr(n,0);
        for(int i=0;i<n;i++){
            if(i<5){
                arr[i] = 1;
            }
            else{
                arr[i] = *min_element(arr.begin()+i-5,arr.begin()+i) +1;
            }
        }
        cout<<arr[n-1]<<endl;
    }
    return 0;
}
*/