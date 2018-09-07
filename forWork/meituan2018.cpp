
#include <iostream>
#include <stdio.h>
#include <string.h>
using namespace std;


//美团 1 AC代码
#define MAXN 100010
int g[MAXN][100];
int f[MAXN];
int isv[MAXN];
int maxn = 0;

void dfs(int curp,int curs)
{
    int i;
    // 当前节点走过了
    isv[curp] = 1;
    // 当前节点是否全部走过，默认为是
    bool isallv = true;
    for(i=0;i<f[curp];i++){
        if( ! isv[g[curp][i]]){
            // 当前节点的第 i 个子节点没有被走过，那么可以走
            isallv = false;
            dfs(g[curp][i],curs+1);
        }
    }
    if(isallv){
        //当前节点的所有子节点都被走过，那么不能再走了，计算走到这儿的最大深度
        if(curs>maxn)
            maxn = curs;
    }
}

int main()
{
    int n;
    while(scanf("%d",&n)!=EOF){
        if(n==0) break;
        memset(g,0,sizeof(g));
        memset(f,0,sizeof(f));
        memset(isv,0,sizeof(isv));
        for(int i=0;i<n-1;i++){
            int a,b;
            scanf("%d%d",&a,&b);
            g[a][f[a]++] = b;
            g[b][f[b]++] = a;
        }
        dfs(1,0);
        printf("%d\n",(n-1)*2-maxn);
    }
    return 0;
}
//2. 通过82
/*
#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 10000

static int n, k, t;
static int buffer_l[MAX_SIZE] = { 0, };
static int buffer_r[MAX_SIZE] = { 0, };


static int IsAppearT(int *p, int l, int r)
{
	int i, j;
	int temp;
	int counter = 0;

	for (i = l - 1; i <= r - 1; ++i)
	{
		temp = p[i];
		for (j = l - 1; j <= r - 1; ++j)
		{
			//把temp和每一个比较，有一次就+1
			if (temp == p[j])
				++counter;
		}

		if (counter >= t)
		{
			return 0;
		}
		counter = 0;
	}

	return -1;
}

static int caclArea(int *p, int len)
{
	int ret = 0;
	int Max = n;
	int temp_l = 1, temp_r = 1;
	int cnt = 0;
	int i;
	for (temp_l = 1; temp_l <= Max; ++temp_l)
	{
		for (temp_r = 1; temp_r <= Max; ++temp_r)
		{
			if ((temp_r - temp_l + 1) == k)
			{
				buffer_l[cnt] = temp_l;
				buffer_r[cnt] = temp_r;
				++cnt;
			}
		}
	}
	for (i = 0; i < cnt; ++i)
	{
		if (IsAppearT(p, buffer_l[i], buffer_r[i]) == 0)
		{
			++ret;
		}
	}

	return ret;
}

int main()
{
	int i;
	int ret;
	int *p;

	scanf("%d %d %d", &n, &k, &t);

	p = ((int *)malloc(n*sizeof(int)));

	for (i = 0; i < n; ++i)
	{
		scanf("%d", p + i);
	}

	ret = caclArea(p, n);

	printf("%d", ret);

}
*///通过38
/*
#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <algorithm>

using namespace std;
int main(){
	int n, t, k;
	while (cin >> n >> k >> t){
		vector<int> arr(n);
		for (int i = 0; i < n; i++){
			cin >> arr[i];
		}
		int sum = 0;
		for (int i = 0; i <= arr.size() + 1 -k; i++){
			map<int, int> map;
			int l = i, r = k + l - 1;
			for (int j = i; j < r; j++){ 
				if (map.find(arr[i]) == map.end()){
					map.insert(std::make_pair(arr[i], 1));
					if (map[arr[i]] == t){
						sum++;
						break;
					}
				}
				else{
					map[arr[i]]++;
					if (map[arr[i]]++ == t){
						sum++;
						break;
					}
				}
			}
		}
		cout << sum << endl;
	}
	return 0;
}
*/