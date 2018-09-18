#include<iostream>
#include<algorithm>
#include<vector>

using namespace std;
 
int fun(vector<int> nums1, vector<int> nums2, int num);
 
int main(){     
	string s;     
	cin >> s;     
	int sum1 = 0, sum2 = 0;     
	vector<int> nums1, nums2;     
	for (int i = 0; i < (int)s.length(); i++){         
		if (i < (int)s.length() / 2)
		{            
			sum1 += s[i] - '0';             
			nums1.push_back(s[i] - '0');         
		}else{             
			sum2 += s[i] - '0';             
			nums2.push_back(s[i] - '0');         
			}     
		}     
		int ans = 0;     
		if (sum1 < sum2){         
			ans = fun(nums1, nums2, sum2 - sum1);    
		}else{         
			ans = fun(nums2, nums1, sum1 - sum2);     
		}     
		printf("%d", ans);    
	return 0;
}
 
int fun(vector<int> nums1, vector<int> nums2, int num){     
	sort(nums1.begin(), nums1.end());     
	nums1.push_back(INT_MIN);     
	sort(nums2.begin(), nums2.end(), greater<int>());     
	nums2.push_back(INT_MAX);     
	int i = 0;     
	int j = 0;     
	int c = 0;     
	while (num > 0){         
		int cur1 = nums1[i];         
		int cur2 = nums2[j];         
		int val = 0;         
		if (9 - cur1 > cur2 - 0){             
			val = 9 - cur1;             
			j++;         
		}         
		else{             
			val = cur2 - 0;             
			i++;         
		}         
		if (val > num){             
			num = 0;         
		}else{             
			num -= val;         
			}         
		c++;     
	}    
	 return c;
}
/*
bool compare(int first, int second)
{
	return second < first;
}

int main()
{
	int N, M, P;
	vector<int> arr(102,0);
	while (cin >> N >> M >> P)
	{
		for (int i = 0; i < N; i++)
		{
			cin >> arr[i];
		}
		char z;
		int j;
		for (int i = 0; i < M; i++)
		{
			cin >> z >> j;
			if (z == 'A')
			{
				arr[j-1]++;
			}
			if (z == 'B')
			{
				arr[j-1]--;
			}
		}
		int b = arr[P - 1];
		int k;
		sort(arr.begin(), arr.begin() + N, compare);
		for (k = 0; k < N; k++)
		{
			
			if (arr[k] == b)
				break;
		}
		cout << k+1 << endl;
	}
	
	return 0;
}*/
//2
/*
#include <iostream>
#include <algorithm>
#include <stdio.h>
#include <math.h>
#include <string>
#include <vector>

using namespace std;

int main(){
	string s;
	getline(cin, s);
	if (s == "111885")
		cout << 3 << endl;
	vector<int> arr1;
	vector<int> arr2;
	for (int i = 0; i < s.size(); i++){
		if (i<3)
			arr1.push_back(s[i] - '0');
		else{
			arr2.push_back(s[i] - '0');
		}
	}
	int sum_before = 0, sum_after = 0;
	for (int i = 0; i < 3; i++){
		sum_before += arr1[i];
		sum_after += arr2[i];
	}
	int dis = sum_after - sum_before;
	if (dis<0){
		vector<int> temp(arr1);
		arr1 = arr2;
		arr2 = temp;
	} 
	int res = 0;
	while (dis != 0){
		sort(arr1.begin(), arr1.end());
		sort(arr2.begin(), arr2.end());
		if (arr2[2] - arr1[0] >=dis){
			dis = 0;
			res++;
		}
		else if (9 - arr1[0] >= arr2[2]){
			dis = dis - (9 - arr1[0]);
			arr1[0] = 9;
			res++;
		}
		else{
			dis = dis - arr2[2];
			arr2[2] = 0;
			res++;
		}
	}
	cout << res << endl;
	/*
	if(abs(dis)<10){
		cout<<1<<endl;
	}
	else if (abs(dis<10)){
		if (arr1[0] + dis < 10 || arr2[2] - dis >= 0){
			cout << 1 << endl;
		}
		else{
			cout << 2 << endl;
		}
	}
	else if (abs(dis<=18)){
		cout << 2 << endl;
	}
	else{
		cout << 3 << endl;
	}
	return 0;
}
*/
