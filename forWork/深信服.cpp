##1 
#include <iostream>
#include <string.h>
#include <stdio.h>

using namespace std;


int main()
{
	int m, n;
	int a[1001];
	int dp[2][1001];
	//memset(dp, 1, sizeof(dp));
	//初始化记录数组
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 1001; j++) {
			dp[i][j] = 1;
		}
	}


	scanf("%d %d", &m, &n); //m是洞的编号，n是天数
	//第i+1天检查的洞的编号
	for (int i = 0; i < n; i++)
		scanf("%d", &a[i]);
	//填表
	for (int i = 0; i < n; i++) {
		for (int j = 1; j <= m; j++) {
			if (j == a[i])
				dp[i % 2][j] = 0;
			if (dp[(i - 1) % 2][2] == 0 && i > 0)
				dp[i % 2][1] = 0;
			if (dp[(i - 1) % 2][m - 1] == 0 && i > 0)
				dp[i % 2][m] = 0;
			if (dp[(i - 1) % 2][j - 1] == 0 && dp[(i - 1) % 2][j + 1] == 0 && i > 0)
				dp[i % 2][j] = 0;
		}
	}

	int index = 0;
	for (int j = 1; j <= m; j++) {
		if (dp[(n - 1) % 2][j] == 1) {
			index = 1;
			break;
		}
	}

	if (index == 1)
		printf("No\n");
	else
		printf("Yes\n");

	return 0;
}

##2
#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
using namespace std;

void soulution(vector<int> nums){
	map<int,int> newmap;
	int index = 0;
	for (int i = 0; i < nums.size(); i++){
		bool isexist = false;
		for (int j = 0; j < index; j++)
		{
			if (newmap.at(j) == nums[i])
				isexist = true;
		}
		if (!isexist){
			newmap[index++] = nums[i];
		}
        if(newmap.size() == 10)
            break;
	}

	cout << newmap.size() << endl;
	for (int i = 0; i < newmap.size(); i++){
		cout << newmap.at(i) << endl;
	}
}
int main(){

	int n;
	while (cin >> n){
		vector<int> arr(n);
		for (int i = 0; i < n; i++){
			cin >> arr[i];
		}
		soulution(arr);
	}
	return 0;
}

###3

###4
#include <iostream>
#include <cstring>
#include <utility>
#include <string>
#include <vector>
using namespace std;

vector<pair<int, string>> fun(const string& str)
{
	vector<string> subs;
	vector<pair<int, string>> res;
	int len = str.size();
	for (int i = 0; i < len; i++)
	{
		subs.push_back(str.substr(i));
	}

	int length;
	string sub;

	//i为子串的长度
	for (int i = 1; i <= len / 2; i++)
	{
		for (int j = 0; 2 * i + j <= len; j++)
		{

			if (subs[j + i].substr(0, i) == subs[j].substr(0, i))
			{
				length = 2 * i;
				sub = subs[j].substr(0, i) + subs[j].substr(0, i);
				res.clear();
				res.push_back(make_pair(length, sub));
			}		
		}
	}

	return res;
}

int main()
{
	string str;
	vector<pair<int, string>> res;
	while (cin >> str)
	{
		res = fun(str);
		if (res.size() == 0)
			cout << 0 << endl;
		else
			cout << res.at(0).first << endl;
	}
	return 0;
}

# ##5:
#include <iostream>
#include <cstring>
#include <utility>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int solution(vector<int> &arr){
    if (arr.size() < 2)
		return arr.size();
	int start = 0, total = 0;
	for (int i = 0; i < arr.size(); i++){
		if (arr[i] == i + 1){
			continue;
		}
		for (int j = i + 1; j < arr.size(); j++){
			if (arr[j] == i + 1){
				swap(arr[start], arr[j]);
				total++;
			 }
		  }
	 }
	return total;
}

int main()
{
	int n;
	while (cin>>n){
		vector<int> arr(n);
		for (int i = 0; i < n; i++){
			cin >> arr[i];
		}
		cout << solution(arr) << endl;
	}
	return	0;
}