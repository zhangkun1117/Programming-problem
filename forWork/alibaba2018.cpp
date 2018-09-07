#include <iostream>
#include <vector>
#include <numeric>
#include <limits>
#include <string>   
#include <set>

// 1.通过0，求所有子串方法有问题。
using namespace std;
int main(int argc, char **argv)
{
	string s;
	int n;
	set<string> set;
	cin >> s;
	cin >> n;
	for (int i = 0; i<n; i++){
		string temp;
		cin >> temp;
		set.insert(temp);
	}
	vector<vector<string>> arr;
	for (int i = 0; i<s.size(); i++)
	{
		vector<string> temp;
		int x = 0;
		int sum = 0;
		for (int j = i; j<s.size() - 1 && x<s.size() - 1; j++)
		{
			//std::cout<<substr(i,i+j);}
			if (set.find(s.substr(x, x + j)) != set.end()){
				temp.push_back(s.substr(x, x + j));
				x = x+j;
				sum += j;
			}
			else{
				temp.clear();
				break;
			}
		}
		if (sum == s.size()+1){
			for (auto it = temp.begin(); it != temp.end(); it++)
			{
				cout << *it <<" ";
			}
			cout << endl;
			arr.push_back(temp);
		}
	}
	int max = 0;
	vector<string> res;
	for (int i = 0; i<arr.size(); i++){
		int ilen = 0;
		for (int j = 0; j<arr[i].size(); j++){
			ilen += pow(arr[i][j].size(), 2);
		}
		if (ilen>max){
			max = ilen;
			res = arr[i];
		}
		else if(ilen == max){
			for (int k = 0; k < arr[i].size() && k < res.size(); k++){
				if (arr[i][k].size() > res[k].size()){
					res = arr[i];
					break;
				}		
			}
		}
	}
	for (int i = 0; i<res.size(); i++){
		cout << res[i] << " ";
	}
	cout << endl;
	return 0;
}