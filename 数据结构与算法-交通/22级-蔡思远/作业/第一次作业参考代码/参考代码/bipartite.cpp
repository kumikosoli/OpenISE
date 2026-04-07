#include <stdio.h>
#include <memory.h>
const int maxn = 401;
int edge[maxn][maxn];
int color[maxn];      //0: uncolored.   -1 +1  : colored black or white.
int n;      //顶点数

// 深度优先搜索函数，用于判断图是否为二分图
bool dfs(int u, int c) {
	color[u] = c;   //对u点进行染色操作
	for (int v = 1; v <= n; v++) //遍历与u点相连的点
		if (edge[u][v] == 1) {
			if (color[v] == c)
				return false;//v点的染色冲突，则不是二分图
			if (!color[v])
				if (!dfs(v, -c))
					return false;//该点未染色，染上相反的颜色.dfs继续搜索
		}
	return true;  //所有点染色完成之后，并且相邻顶点没有同色，则为二分图
}

int main() {
	int k;
	scanf("%d", &k);  //读取测试用例数
	for (int m = 1; m <= k; m++) {
		scanf("%d", &n);
		memset(edge, 0, sizeof(edge)); //初始化边数组
		memset(color, 0, sizeof(color)); //初始化颜色数组
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= n; j++)
				scanf("%d", &edge[i][j]); //读取每条边的顶点和权重
		bool flag = false;
		for (int i = 1; i <= n; i++) {
			if (!color[i]) {
				if (!dfs(i, 1)) {
					printf("No\n");
					flag = true;
					break;
				}
			}
		}
		if (!flag)
			printf("Yes\n");
	}
	return 0;
}



