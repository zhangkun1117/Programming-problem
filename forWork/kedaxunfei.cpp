
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
//2.AC代码
int main(){
	int n;
	while (cin >> n){
		vector<int> arr(n);
		for (int i = 0; i<n; i++){
			cin >> arr[i];
		}
		int sum=0;
		while (1){
			//判断序列是否存在降序
			bool isdec = false;
			for (int i = 1; i < arr.size(); i++){
				if (arr[i] < arr[i - 1]){
					isdec = true;
					break;
				}
			}
			if (!isdec) break;
			sum++;
			for (int i = arr.size() - 2; i >= 0; i--){
				if (arr[i]>arr[i + 1])
					arr.erase(arr.begin()+i+1);					
			}
		}
		cout << sum << endl;
	}
	return 0;
}
/*
// 1.AC代码
int main() {
	int T;
	int n, X;
	while(cin >> T){
    	while (T--) {
	    	cin >> n >> X;
		    arrtor<int> arr(n);
		    for (int i = 0; i<n; ++i) {
                cin>>arr[i];
    		}
	    	sort(arr.begin(), arr.end());
		    int sum = accumulate(arr.begin(), arr.end(), 0);
		    int allsum = X*n;
		    int dis = allsum - sum;
		    if (dis > 0) {
			    for (int i = 0,temp=0; i<n; ++i) {
				    temp += (100 - arr[i]);
				    if (temp >= dis) {
					    cout << i + 1 << endl;
					    break;
				    }
			    }
		    }
		    else {
                cout<<0<<endl;
		    }
	    }
    }
	return 0;
}
*/
