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

int maxsum(vector<int> nums,int begin){
    vector<int> temp(nums.size(),0);
    temp[begin] =nums[begin];
    int maxpos =0;
    for(int i=begin+1;i<nums.size();i++){
        temp[i] = temp[i-1]+nums[i];
    }
    int pos = distance(temp.begin(),max_element(temp.begin(),temp.end()));
    return pos;
}
//快手校园招聘
int main(){
    int N,M;
    cin>>N>>M;
    vector<int> arr(N,0);
    for(int i=0;i<N;i++)    {   
        cin>>arr[i];
    }
    vector<vector<int> > result;
    int maxpos =0;
    int lastmaxpos=0;
    while(maxpos<=N){
        if(arr[lastmaxpos]<0){
            vector<int> temp(arr.begin()+lastmaxpos,arr.begin()+lastmaxpos+1);
            result.push_back(temp);
        }else{
            maxpos = maxsum(arr,lastmaxpos);
            vector<int> temp(arr.begin()+lastmaxpos,arr.begin()+maxpos);
            result.push_back(temp);
        }
    }
    vector<int> res;
    for(int i=0;i<result.size();i++){
        int sum=0;
        for(int j=0;j<result[i].size();j++){
            sum +=result[i][j];
        }
        res.push_back(sum);
    }
    sort(res.begin(),res.end());
    int p=0;
    for(int i=0;i<M && i<res.size();i++){
        p+=res[i];
    }
    cout<<p<<endl;
    return 0;
}
/*
int main ()
{
    string s;

    while(cin>>s){

        vector<int>nums;

        char *str = (char *)s.c_str();//string --> char
        const char *split = ",";
        char *p = strtok (str,split);//逗号分隔依次取出

        int a;
        while(p != NULL) {
            sscanf(p, "%d", &a);//char ---> int
            nums.push_back(a);
            p = strtok(NULL,split);
        }
        int isize =nums.size();
        vector<int> arr(isize,0);
        //arr[0] = nums[0];
        //arr[1] = min(arr[0]+nums[0],nums[1]);  
        for(int i=2;i<isize;i++){
            arr[i] = min(arr[i-1] + nums[i-1],arr[i-2]+nums[i-2]);
        }
        cout<<arr[isize-1]+nums[isize-1]<<endl;
    } 
    return 0;
}*/