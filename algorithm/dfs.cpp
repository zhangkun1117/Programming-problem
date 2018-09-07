/**
 * 无向图的深度优先遍历
 */
#include <iostream>
#include <climits>
using namespace std;
int book[101] = {0}, sum, n, m, e[101][101] = {0};
void dfs(int cur) {
    cout << cur << " ";
    sum++;
    if (sum == n)return;
    for (int i = 1; i <= n; i++) {  //循环达到回溯的效果
        if (book[i] == 0 && e[cur][i] == 1) {
            book[i] = 1;
            dfs(i);
        }
    }
    return;
}
int main(int argc, const char *argv[]) {
    cin >> n >> m;  //n个节点，m条边
    for (int i = 1; i <= n; i++)    //初始化
        for (int j = 1; j <= n; j++) {
            if (i == j)
                e[i][j] = 0;
            else
                e[i][j] = INT_MAX;
        }
    int a, b;
    for (int k = 1; k <= m; k++) {  //矩阵表示
        cin >> a >> b;
        e[a][b] = 1;
        e[b][a] = 1;
    }
    book[1] = 1;
    dfs(1);
    return 0;
}