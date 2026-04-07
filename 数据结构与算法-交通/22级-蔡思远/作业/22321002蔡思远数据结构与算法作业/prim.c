#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAXN 100000
#define MAXM 500000
#define INF 1000000000

typedef struct {
    int next, cost;
} Edge;

typedef struct {
    int vex, cost;
} HeapNode;

HeapNode heap[MAXM];
int heapSize = 0;

Edge edges[MAXM];
int head[MAXN], next[MAXM];

int dist[MAXN];
int parent[MAXN];
bool flag[MAXN];
int edgeCount = 0;

// 添加边到图的邻接表中
void addEdge(int u, int v, int c) {
    edges[edgeCount].next = v;
    edges[edgeCount].cost = c;
    next[edgeCount] = head[u];
    head[u] = edgeCount++;
}

// 二叉堆向上调整
void shiftUp(int i) {
    while (i > 0) {
        int parent = (i - 1) / 2;
        if (heap[parent].cost <= heap[i].cost) break;
        HeapNode temp = heap[i];
        heap[i] = heap[parent];
        heap[parent] = temp;
        i = parent;
    }
}

// 二叉堆向下调整
void shiftDown(int i) {
    int minIndex = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    if (left < heapSize && heap[left].cost < heap[minIndex].cost) {
        minIndex = left;
    }
    if (right < heapSize && heap[right].cost < heap[minIndex].cost) {
        minIndex = right;
    }
    if (i != minIndex) {
        HeapNode temp = heap[i];
        heap[i] = heap[minIndex];
        heap[minIndex] = temp;
        shiftDown(minIndex);
    }
}

// 向堆中插入新节点
void insert(HeapNode node) {
    heap[heapSize] = node;
    shiftUp(heapSize);
    heapSize++;
}

// 从堆中提取最小节点
HeapNode find_min_node() {
    HeapNode result = heap[0];
    heap[0] = heap[--heapSize];
    shiftDown(0);
    return result;
}

// Prim算法的实现
void prim(int start, int n) {
    // 初始化所有顶点
    for (int i = 0; i < n; i++) {
        dist[i] = INF;
        flag[i] = false;
        parent[i] = -1;
    }
    dist[start] = 0;
    insert((HeapNode){start, 0});
    // 构建最小生成树
    while (heapSize > 0) {
        HeapNode minNode = find_min_node();
        int u = minNode.vex;
        if (flag[u]) continue; // 如果u已经被加入到最小生成树中，则跳过当前循环
        flag[u] = true;
        // 邻接表存储图
        for (int i = head[u]; i != -1; i = next[i]) {
            int v = edges[i].next;
            int cost = edges[i].cost;
            // 如果v还没有被加入到最小生成树中，且到达v的当前边的费用小于已知的最小费用，则更新v
            if (!flag[v] && dist[v] > cost) {
                dist[v] = cost;
                parent[v] = u;
                insert((HeapNode){v, cost});
            }
        }
    }
    for (int i = 1; i < n; i++) {
        if (parent[i] != -1) {
            printf("%d\n", dist[i]);
        }
    }
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    memset(head, -1, sizeof(head));
    for (int i = 0; i < m; i++) {
        int u, v, c;
        scanf("%d %d %d", &u, &v, &c);
        u--; v--; // 将顶点编号减一（数组从0开始）
        addEdge(u, v, c);
        addEdge(v, u, c);  
    }
    prim(0, n); // 从顶点0开始生成最小生成树
    return 0;
}
