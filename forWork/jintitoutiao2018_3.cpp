#include <iostream>
#include <vector>
#include <numeric>
#include <limits>
#include <string>   
#include <set>
#include <algorithm>
#include <map>

using namespace std;
//今日头条第三次笔试
vector<string> subIP(string s, int cont);
void combine(const string &temp1, vector<string> &temp2);

vector<string> subIP(string s, int cont) {
        vector<string> result;
        if (s.empty() || !cont)
            return result;
        for (int i = 1; i <= 3; ++i) {
            string temp1 = s.substr(0, i);
            if ('0' == temp1[0] && temp1.length()>1)
                break;
            if (atoi(temp1.c_str()) > 255 || i > s.length())
                break;
            string temp = s.substr(i);
            vector<string> temp2 = subIP(temp, cont - 1);
            combine(temp1, temp2);
            if (temp.empty() && temp2.empty() && cont - 1 == 0)
                result.push_back(temp1);
            else
                result.insert(result.end(), temp2.begin(), temp2.end());
        }
        return result;
}
void combine(const string &dst, vector<string> &src){
    for (auto it = src.begin(); it != src.end(); ++it) {
        it->insert(0, dst + ".");
    }
}

int main() {
    string s;
    cin >> s;
    vector<string> arr = subIP(s, 4);
    cout <<arr.size()<< endl;
    return 0;
}

/*
void bfs(vector<vector<int>>& arr, int i, int j, int& sum)
{
	if (i<0 || i>arr.size() - 1 || j<0 || j>arr[0].size() - 1 || arr[i][j] == 0)
		return;
	arr[i][j] = 0;
	++sum;
	bfs(arr, i - 1, j, sum);
	bfs(arr, i + 1, j, sum);
	bfs(arr, i, j - 1, sum);
	bfs(arr, i, j + 1, sum);
	return;
}
int main()
{
    int M;
	cin >> M;	
	vector<vector<int> > arr(M, vector<int>(M, 0));
	for (int i = 0; i<M; ++i)
	{
		for (int j = 0; j<M; ++j)
		{
			cin >> arr[i][j];
		}
	}
	int sum = 0, maxsum = 0;
	for (int i = 0; i != M; ++i)
	{
		for (int j = 0; j != M; ++j)
			if (arr[i][j] == 1)
			{
			    int tempMaxSum = 0;
			    bfs(arr, i, j, tempMaxSum);
			    ++sum;
			    if(tempMaxSum>maxsum)
			    	maxsum = tempMaxSum;
			}
	}
	cout << sum << endl;
	return 0;
}*/
/*
//第一题：字符串
int main()
{
    string str;
    while(cin>>str)
    {
        map<char, int> map;
        for (int i=0; i<str.length(); i++)
            map[str[i]] = -1;
        int pre = -1, Max = 0;
        for (int i=0; i<str.length(); i++){
            pre = max(pre, map[str[i]]);
            Max = max(Max, i-pre);
            map[str[i]] = i;
        }
        cout<<Max<<endl;
    }
    return 0;
}
*/
/*
int changPosition(vector<vector<int>> arr,vector<int> &visit,vector<int> &notvisit){
    int num =0;
    vector<int> temp = notvisit;  
    for(int i=0;i<visit.size();i++){
        for(int j=0;j<temp.size();j++){
            if(arr[temp[j]][visit[i]] ==1){
                visit.push_back(temp[j]);
                num++;
            }
        }
    }
    notvisit = temp;
    return num;
}
int main(){
    int N,M;
    cin>>N>>M;
    vector<vector<int> > arr(N,vector<int>(N,0));
    for(int i=0;i<N;i++){
        arr[i][i] =1;
    }
    for(int i=0;i<M;i++){
        int first,second;
        cin>>first>>second;
        arr[first-1][second-1] =1;
    }
    int sum =0;
    for(int i=0;i<N;i++){
        vector<int> visit;
        vector<int> notvisit;
        for(int j=0;j<N;j++){
            if(arr[j][i] == 1)
                visit.push_back(j);
            else
                notvisit.push_back(j);
        }
        while(changPosition(arr,visit,notvisit) >=1){};
        if(visit.size() == N)
            sum++;
    }
    cout<<sum<<endl;
    return 0;
}
*/

/*
void bfs(vector<vector<int>>& grid, int i, int j, int& sum)
{
	if (i<0 || i>grid.size() - 1 || j<0 || j>grid[0].size() - 1 || grid[i][j] == 0)
		return;
	grid[i][j] = 0;
	++sum;
	bfs(grid, i - 1, j, sum);
	bfs(grid, i + 1, j, sum);
	bfs(grid, i, j - 1, sum);
	bfs(grid, i, j + 1, sum);
	return;
}
int main()
{
    int M;
	cin >> M;	
	vector<vector<int> > grid(M, vector<int>(M, 0));
	for (int i = 0; i<M; ++i)
	{
		for (int j = 0; j<M; ++j)
		{
			cin >> grid[i][j];
			cin.get();
		}
	}
	int sum = 0, maxsum = 0;
	for (int i = 0; i != M; ++i)
	{
		for (int j = 0; j != M; ++j)
			if (grid[i][j] == 1)
			{
			int tmpMax = 0;
			bfs(grid, i, j, tmpMax);
			++sum;
			if (tmpMax>maxsum)
				maxsum = tmpMax;
			}
	}
	cout << sum << endl;
	return 0;
}
*/
/*
vector<string> subIP(string s, int cont);
void combine(const string &temp1, vector<string> &temp2);

vector<string> subIP(string s, int cont) {
        vector<string> result;
        if (s.empty() || !cont)
            return result;
        for (int i = 1; i <= 3; ++i) {
            string temp1 = s.substr(0, i);
            if ('0' == temp1[0] && temp1.length()>1)
                break;
            if (atoi(temp1.c_str()) > 255 || i > s.length())
                break;
            string temp = s.substr(i);
            vector<string> temp2 = subIP(temp, cont - 1);
            combine(temp1, temp2);
            if (temp.empty() && temp2.empty() && cont - 1 == 0)
                result.push_back(temp1);
            else
                result.insert(result.end(), temp2.begin(), temp2.end());
        }
        return result;
}
void combine(const string &dst, vector<string> &src){
    for (auto it = src.begin(); it != src.end(); ++it) {
        it->insert(0, dst + ".");
    }
}

int main() {
    string s;
    cin >> s;
    vector<string> arr = subIP(s, 4);
    cout <<arr.size()<< endl;
    return 0;
}

*/
/*2

int getAGroup(vector<vector<int> > &A, vector<vector<int> > &B, int i, int j) {
    if (i<0 || j<0 || i>A.size()-1 || j>A[0].size()-1 || B[i][j]==1 || A[i][j]==0)
        return 0;
    else {
        B[i][j] = 1;
        return 1+getAGroup(A, B, i-1, j-1)+getAGroup(A, B, i-1, j)+getAGroup(A, B, i-1, j+1)+getAGroup(A, B, i, j-1)+getAGroup(A, B, i, j+1)+getAGroup(A, B, i+1, j-1)+getAGroup(A, B, i+1, j)+getAGroup(A, B, i+1, j+1);
    }
}

int main()
{
    int M, t;
    scanf("%d,%d", &M);
    vector<vector<int> > A(M, vector<int> (M, 0));
    vector<vector<int> > B(M, vector<int> (M, 0));
    for (int i=0;i<M;++i) {
        for (int j=0;j<M-1;++j) {
            scanf("%d,", &t);
            A[i][j] = t;
            B[i][j] = 0;
        }
        scanf("%d", &t);
        A[i][M-1] = t;
        B[i][M-1] = 0;
    }
    int count = 0, max_num = 0;
    for (int i=0;i<M;++i) {
        for (int j=0;j<M;++j) {
            if (A[i][j]==1 && B[i][j]==0) {
                count++;
                int num = getAGroup(A, B, i, j);
                max_num = num>max_num?num:max_num;
            }
        }
    }
    cout << count<<endl;
    return 0;
}*/
/*
// 1.最长重复子串

using namespace std;
int lengthOfLongestSubstring(string s) {
	int start, end;
	string count = "";
	string str = "";
	for (start = 0; start<s.length(); start++){
		for (end = start + 1; end <= s.length(); end++){
			str = s.substr(start, end);
			if (end == s.length()){
				if (count.length() < str.length()){
					count = str;
				}
				break;
			}
			else{
				if (str.find(s.find(end, end + 1))){
					if (count.length() < str.length()){
						count = str;
					}
					break;
				}
			}
		}
	}
	return count.length();
}

int main(){
    string s;
    while(cin>>s){
        cout<<lengthOfLongestSubstring(s)<<endl;
    }
    return 0;
}*/
