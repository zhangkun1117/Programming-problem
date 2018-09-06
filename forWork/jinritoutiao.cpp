
/*今日头条题目*/
/*
int main(){
	int n;
	cin >> n;
	for (int i = 0; i < n; i++){
		int m; cin >> m;
		vector<string> arr(m);
		for (int j = 0; j < m; j++){
			cin >> arr[j];
		}

		cout << "Yeah" << endl;
	}
	return 0;
}
*/
/*//4

int main(){
	long long int n;
	int m;
	while (cin >> n >> m){
		vector<int> arr(n);
		for (long long int i = 0; i < n; i++){
			cin >> arr[i];
		}
		for (int i = 1; i < m; i++){
			arr.insert(arr.end(),arr.begin(),arr.begin() +n);
		}
		vector<int> low(n*m, 0);
		low[0] = arr[0];
		int now=0;
		for (long long int i = 1; i < n*m; i++){
			if (arr[i]>low[now]) 
				low[++now] = arr[i];
			  else
			 {
				  long long int pos = lower_bound(low.begin(), low.begin() + now, arr[i]) - low.begin();
				   low[pos] = arr[i];
			  }
		}
		cout << now+1 << endl;		
	}
}*/

/*int infect(vector<vector<int>> &m, int i, int j, int N, int M); 

int countIslands(vector<vector<int>> &m,int N,int M,int &numsize) {
	//判断2维数组合法
	if (m.size() == 0) {
		return 0;
	}
	//res标记为1的元素，统计个数。
	int res = 0;
	//如果发现为1的元素，就去感染他周围（山下左右）的元素
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (m[i][j] == 1) {
				res++;
				int num = infect(m, i, j, N, M)+1;
				numsize = numsize>num ? numsize : num;
			}
		}
	}
	return res;
}
int infect(vector<vector<int>> &m, int i, int j, int N, int M) {
	//元素下标越界或！=1退出
	if (i < 0 || i >= N || j < 0 || j >= M || m[i][j] != 1) {
		return 0;
	}
	m[i][j] =0;
	int n1 = infect(m, i + 1, j, N, M);//上
	int n2 = infect(m, i - 1, j, N, M);//下
	int n3 = infect(m, i, j - 1, N, M);//作
	int n4 =infect(m, i, j + 1, N, M);//
	int n5 = infect(m, i - 1, j-1, N, M);
	int n6 = infect(m, i - 1, j +1, N, M);
	int n7 = infect(m, i + 1, j - 1, N, M);
	int n8 = infect(m, i + 1, j + 1, N, M);
	return n1 + n2 + n3 + n4+n5+n6+n7+n8+1;
}
int main()
{
	string nm;
	cin >> nm;
	istringstream is(nm);
	string temp;
	vector<int> arr;
	while (getline(is, temp, ',')) {
		arr.push_back(stoi(temp));
	}
	int n = arr[0], m = arr[1];
	
	vector<vector<int>> array(n, vector<int>(m));
	for (int i = 0; i<n; i++){
		string s;
		cin >> s;
		istringstream is(s);
		string tmp;
		int j = 0;
		while (getline(is, tmp, ',')) {
			array[i][j] = stoi(tmp);
			j++;
			//cout << array[i][j] << " ";
		}
		//cout << endl;
				
	}

	int num = 0, numsize = 0;
	num = countIslands(array, n, m, numsize);
	cout << num << "," << numsize << endl;
	return 0;
}*/
/*
bool canPartition(vector<int> &nums) {
	// write your code here
	int sum = 0;
	for (auto c : nums)
		sum += c;
	if (sum % 2 != 0)
		return false;
	else
		sum /= 2;
	int len = nums.size();
	vector<vector<bool>> dp(len + 1, vector<bool>(sum + 1, false));
	for (int i = 0; i <= len; ++i)
		dp[i][0] = true;
	for (int i = 1; i <= len; ++i)
	{
		for (int j = 1; j <= sum; ++j)
		{
			if (j >= nums[i - 1])
				dp[i][j] = dp[i - 1][j] || dp[i - 1][j - nums[i - 1]];
			else
				dp[i][j] = dp[i - 1][j];
		}
	}
	return dp[len][sum];
}
int main(){
	int n, m;
	while (cin >> n){
		vector<int> arr(n);
		vector<int> value(n);
		for (int i = 0; i < n; i++){
			cin >> arr[i]>>value[i];
		}

	}
}
*/
