#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <set>
using namespace std;

//360笔试


int main(){
	int n;
	while (cin >> n){
		vector<int> arr1(n);
		vector<int> arr2(n);
		for (int i = 0; i < n; i++){
			cin >> arr1[i];
		}
		for (int i = n-1; i >= 0; i--){
			cin >> arr2[i];
		}
		vector<vector<int> > vec(n+1, vector<int>(n+1,0));
		int res = 0;
		for (int i = 0; i < n; i++){
			for (int j = 0; j < n; j++){
				if (arr1[i] == arr2[j]){
					vec[i+1][j+1] = vec[i][j+1] + 1;
					res = max(vec[i][j], res);
				}
				else{
					vec[i+1][j+1] = max(vec[i][j+1], vec[i+1][j]);
					res = max(vec[i][j], res);
				}
			}
		}
		cout << vec[n][n] << endl;

	}
	return 0;
}
/*
int main(){
	int n, m;
	while (cin >> n>>m){
		vector<int> arr(n);
		for (int i = 0; i < n; i++){
			cin >> arr[i];
		}
		int q;
		cin >> q;
		for (int i = 0,l,r; i < q; i++){
			cin >> l >> r;
			set<int> set;
			for (int j = l-1; j <= r-1; j++){
				set.insert(arr[j]);
			}
			int res = set.size()>m ? m : set.size();
			cout << res << endl;
		}

	}
}*/
/*
int main(){
	int n;
	while (cin >> n){
		long long int xmin, xmax, ymin, ymax;
		cin >> xmin >> ymin;
		xmax = xmin;
		ymax = ymin;
		for (int i = 1,x,y; i < n; i++){		
			cin >> x >> y;
			xmin = (x < xmin) ? x : xmin;
			xmax = (x > xmax) ? x : xmax;
			ymin = (y < ymin) ? y : ymin;
			ymax = (y > ymax) ? y : ymax;
		}
		long long int  len = (xmax - xmin) >(ymax - ymin) ? (xmax - xmin) : (ymax - ymin);
		long long int area = len * len;
		cout << area << endl;
	}
}*/