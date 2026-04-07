#include <stdio.h>
const int maxn = 50010;

struct node {
	int x;   //节点的值
	node *next;
};

int n, m;
node *head[maxn];  // 注意：头节点的x存的是入度。

void topo() {
	int que[maxn], l = 0, r = 0;
	for (int i = 1; i <= n; i++)
		if (head[i]->x == 0)
			que[r++] = i;  // 如果结点的入度为0，将其加入队列
	while (l < r) {
		int s = que[l++];
		printf("%d ", s);
		node *p = head[s]->next;    // 获取队首元素的下一个结点
		while (p) {  // 遍历队首元素的所有后继结点
			head[p->x]->x--;
			if (head[p->x]->x == 0)
				que[r++] = p->x;  // 如果后继结点的入度为0，将其加入队列
			p = p->next;
		}
	}
}

int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) { // 初始化所有结点
		head[i] = new node;
		head[i]->x = 0;
		head[i]->next = NULL;
	}
	for (int i = 1; i <= m; i++) {
		int x, y;
		scanf("%d%d", &x, &y);
		node *p = new node;
		p->x = y;
		p->next = head[x]->next;
		head[x]->next = p;
		head[y]->x++; //y的入度加一
	}
	topo();
	return 0;
}