#include <bits/stdc++.h>
using namespace std;

/*//第一题
int main(){
    vector<string> str = {"1","2","3","4"};
    long long int n;

    while(cin>>n){
        if(n<=4){
            cout<<str[n-1]<<endl;
            continue;
        }        
       // cout<<floor(log10f(n+4)/log10f(2))<<endl;
        int x = floor(log10f(n+4)/log10f(2))-2;
        float dis = n - (pow(2,x+2)-4);
        int m = pow(2,x);
        int res = ceil(dis/m);
        if (res == 0)
            res =3;
        cout<<str[res-1]<<endl;
    }
    return 0;
}*/
/*//第二题
int isbig(vector<char> str1,vector<char> str2){
	int a = 0, b = 0;
	for (int i = 0; i < str1.size(); i++){
		if ((str1[i] - 'a') < (str2[i] - 'a')){
			a++;
		}
		else if ((str1[i] - 'a') > (str2[i] - 'a')){
			b++;
		}
	}
	return a > b ? true : false;
}
int main(){
	int n, m;
	while (cin >> n >> m){
		vector<string> str;
		for (int i = 0; i <= m; i++){
			string st;
			getline(cin, st);
			str.push_back(st);
		}
		vector<vector<char> > array(n);
		for (int i = 0; i < n; i++){
			for (int j = 1; j <= m; j++){
				array[i].push_back(str[j].at(i));
			}
		}
		for (int i = 0; i < n; i++){
			sort(array[i].begin(), array[i].end());
		}
		vector <vector <int>   >   res(n);
		for (int i = 0; i < n; i++)
			res[i].resize(n);
		for (int i = 0; i < n - 1; i++){
			for (int j = i + 1; j < n; j++){
				res[i][j] = isbig(array[i], array[j]);
			}
		}
		vector<int> a(n,0);
		for (int i = 0; i < n; i++){
			int temp = 0;
			for (int j = 0; j < n; j++)
				temp = temp + res[i][j];
			a[i] = temp;
		}
		bool isexist = false;
		for (int i = 0; i < n; i++){
			if (a[i] == m){
				cout << i << endl;
				isexist = true;
			}
		}
		if (!isexist)
			cout << -1 << endl;
	}
	return 0;
}*/

int main()
{
    vector<int> array;
    int w;
    while(cin>>w){
        array.push_back(w);
    }
    if (array.size() <= 1)
    {
        cout << array.size() << endl;
    }
    sort(array.begin(), array.end(), greater<int>());
    int count = 0;
    for (auto it = array.begin(); it != array.end() && *it == 100; it++, count++){}
    int res = count / 3;
    for (int i = res * 3, j = array.size() - 1; i <= j;)
    {
        if (array[i] + array[j] <= 300)
        {
            res++;
            i++;
            j--;
        }
        else
        {
            res++;
            j--;
        }
    }
    cout << res << endl;
    return 0;
}
/*
#include <iostream>
#include <vector>
#include <algorithm>
  using namespace std;
  int main()
{
         int L = 0, w, wsum = 0;
       vector<int> weight;
         while (cin >> w)          weight.push_back(w);
              sort(weight.begin(), weight.end());
         int left = 0, right = weight.size() - 1;
       int count = 0;
         for (int i = 0; i < weight.size(); ++i)          if (weight[i] == 100)              ++count;
         if (count >= 3)
    {
              
             L = count / 3;
                 left = L * 3;
            
    }
         while (left < right)    
         
    {
                 if (weight[left] + weight[right] > 300)         
        {
                       
                 --right;
                       
                 ++L;
                    
        }
                 else
        {
                         ++left;
                       
                 --right;
                       
                 ++L;
                    
        }
                     
    }
         if (left == right)          ++L;
         cout << L << endl;
         system("pause");
        return 0;
}
*/