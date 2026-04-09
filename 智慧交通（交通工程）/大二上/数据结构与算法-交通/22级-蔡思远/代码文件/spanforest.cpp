#include <stdio.h>


const int MAX_NODES = 5001;
int nodeCount, edge = 0;
int visited[MAX_NODES];

struct EdgeNode {
    int vex;
    int isConnected;
    EdgeNode* next;
};

EdgeNode* List[MAX_NODES];

// 深度优先搜索
void DFS(int v) {
    visited[v] = 1;
    EdgeNode* currentEdge = List[v]->next;
    while (currentEdge != NULL) {
        int targetVex = currentEdge->vex;
        if (visited[targetVex] == 0) {
            edge += 1;
            currentEdge->isConnected = 1;
            EdgeNode* otherVex = List[targetVex]->next;
            while (otherVex) {
                if (otherVex->vex == v)
                    otherVex->isConnected = 1;
                otherVex = otherVex->next;
            }
            DFS(targetVex);
        }
        currentEdge = currentEdge->next;
    }
}

// 遍历所有节点
void traverseNodes() {
    for (int i = 1; i <= nodeCount; i++)
        visited[i] = 0;
    for (int i = 1; i <= nodeCount; i++)
        if (visited[i] == 0)
            DFS(i);
}

int main() {
    scanf("%d", &nodeCount);
	// 初始化邻接表
    for (int i = 1; i <= nodeCount; i++)
    {
        List[i] = new EdgeNode;
        List[i]->vex = 0;
        List[i]->next = NULL;
    }
    for (int i = 1; i <= nodeCount; i++) {
        int edgeCount;
        scanf("%d", &edgeCount);
        List[i]->vex = edgeCount;
        EdgeNode* rear = List[i];
		// 建立邻接表
        for (int j = 1; j <= edgeCount; j++)
        {
            int target;
            scanf(" %d", &target);
            EdgeNode* newEdge = new EdgeNode;
            newEdge->vex = target;
            newEdge->isConnected = 0;
            rear->next = newEdge;
            rear = newEdge;
        }
        rear->next = NULL;
    }
    traverseNodes();
    printf("%d\n", edge);
    for (int i = 1; i <= nodeCount; i++) {
        printf("%d ", List[i]->vex);
        EdgeNode* currentEdge = List[i]->next;
        while (currentEdge) {
            printf("%d ", currentEdge->isConnected);
            currentEdge = currentEdge->next;
        }
        printf("\n");
    }
}
