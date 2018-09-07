/**
 * 图的广度优先遍历
 */
#include <iostream>
#include <climits>
using namespace std;
int main() {
    int n, m, a, b, cur, book[101] = {0}, e[101][101] = {0};
    int que[101], head = 1, tail = 1;
    cin >> n >> m; //n个节点，m条边
    for (int i = 1; i <= n; i++)   //初始化
        for (int j = 1; j <= n; j++) {
            if (i == j)
                e[i][j] = 0;
            else
                e[i][j] = INT_MAX;
        }
    for (int i = 1; i <= m; i++) {  //图的矩阵表示
        cin >> a >> b;
        e[a][b] = 1;
        e[b][a] = 1;
    }
    que[1] = 1;
    tail++;
    book[1] = 1;  //走过的标记为1
    while (head < tail) {
        cur = que[head];
        for (int i = 1; i <= n; i++) { //当前顶点往下的所有可能都存到队列中去
            if (book[i] == 0 && e[cur][i] == 1) {
                que[tail] = i;
                tail++;
            }
            if (tail > n)
                break;
        }
        head++; //表示当前点遍历结束，下个点
    }
    for (int i = 1; i <= n; i++) {
        cout << que[i] << " ";
    }
    return 0;
}