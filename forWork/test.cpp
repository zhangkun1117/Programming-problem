#include <iostream>
#include <stdio.h>
#include <string.h>
using namespace std;
#define MAXN 100010
int g[MAXN][100];
int f[MAXN];
int isv[MAXN];
int maxn = 0;

void dfs(int curp, int curs)
{
	int i;
	// 当前节点走过了
	isv[curp] = 1;
	// 当前节点是否全部走过，默认为是
	bool isallv = true;
	for (i = 0; i<f[curp]; i++){
		if (!isv[g[curp][i]]){
			// 当前节点的第 i 个子节点没有被走过，那么可以走
			isallv = false;
			dfs(g[curp][i], curs + 1);
		}
	}
	if (isallv){
		//当前节点的所有子节点都被走过，那么不能再走了，计算走到这儿的最大深度
		if (curs>maxn)
			maxn = curs;
	}
}

int main()
{
	int n;
	while (scanf("%d", &n) != EOF){
		if (n == 0) break;
		memset(g, 0, sizeof(g));
		memset(f, 0, sizeof(f));
		memset(isv, 0, sizeof(isv));
		for (int i = 0; i<n - 1; i++){
			int a, b;
			scanf("%d%d", &a, &b);
			g[a][f[a]++] = b;
			g[b][f[b]++] = a;
		}
		dfs(1, 0);
		printf("%d\n", (n - 1) * 2 - maxn);
	}
	return 0;
}