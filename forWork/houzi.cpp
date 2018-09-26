#include <iostream>
#include <vector>
#include <numeric>
#include <limits>
#include <string>   
#include <set>
#include <algorithm>
#include <map>
#include <deque>

using namespace std;
int main(){
    int size,allowedChanges;
    string s;
    cin>>size>>allowedChanges;
    cin>>s;
    s = '0'+s;
    int maxlen =0;
    deque<int> que;
    que.push_back(0);
    for(int i=0,j = 1;j<s.size();j++){
        if(s[i] == '0'){
            que.push_back(i);
            cout<<i<<endl;
        }
        if(que.size() == allowedChanges+2){
            maxlen = max(maxlen,que.back() - que.front()+1);
            que.pop_front();
        }
    }
    cout<<maxlen<<endl;
    return 0;
}