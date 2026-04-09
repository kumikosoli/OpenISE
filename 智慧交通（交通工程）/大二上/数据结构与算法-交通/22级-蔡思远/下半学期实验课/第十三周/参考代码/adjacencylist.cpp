#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#define MAX_VEX  100 /* 最大顶点数，应由用户定义 */
typedef int VexType;
typedef int InfoType;

bool flag = false;
int color[MAX_VEX];

typedef struct ArcNode {     //边表节点
	int adjvex;
	struct 	ArcNode *nextarc;
} ArcNode;

typedef struct {			//顶点表节点
	int data;
	int degree;
	ArcNode *firstarc;
} AdjList;

typedef struct {				// Adjacency Matrix Graph
	char kind;
	int vexnum, arcnum;          //图的当前点数和边数
	AdjList AdjList[MAX_VEX];      //顶点表
} ALGraph;

ALGraph *Create_Graph(ALGraph *G) {
	G->vexnum = 0 ;     //初始化顶点个数
	return (G) ;
}

// 定位顶点的函数，返回顶点vp在图中的位置
int LocateVex(ALGraph *G, VexType vp) {
	int  k;
	for (k = 0 ; k < G->vexnum ; k++)
		if (G->AdjList[k].data == vp)
			return (k) ;
	return (-1) ;    /*  图中无此顶点  */
}

int  AddVertex(ALGraph *G, VexType vp) {
	if  (G->vexnum >= MAX_VEX) {
		return (-1) ;
	}
	if  (LocateVex(G, vp) != -1) {
		return (-1) ;
	}
	G->AdjList[G->vexnum].data = vp ;
	G->AdjList[G->vexnum].degree = 0 ;
	G->AdjList[G->vexnum].firstarc = NULL ;
	return (++G->vexnum) ;
}

int  AddArc(ALGraph *G, InfoType vex1, InfoType vex2) {
	if (vex1 == vex2)
		return (-1);
	ArcNode *q;
	int k = LocateVex(G, vex1)  ;
	int j = LocateVex(G, vex2)  ;
	if (k == -1 || j == -1) {
		return (-1);
	}

	q = (ArcNode *)malloc(sizeof(ArcNode)) ;
	q->adjvex = j ;
	q->nextarc = NULL; /*  边的末尾表结点赋值   */

	q->nextarc = G->AdjList[k].firstarc;
	G->AdjList[k].firstarc = q; /*建立正邻接链表用*/
	return (1);
}

int  DeleteArc(ALGraph *G, InfoType vex1, InfoType vex2) {
	ArcNode *p, *q ;
	if (vex1 == vex2)
		return (-1);
	int k = LocateVex(G, vex1)  ;
	int j = LocateVex(G, vex2)  ;
	if (k == -1 || j == -1) {
//		printf("Arc’s Vertex do not existed !\n") ;
		return (-1);
	}
	p = G->AdjList[k].firstarc;
	if (p->adjvex == j) {
		G->AdjList[k].firstarc = G->AdjList[k].firstarc->nextarc;
		free(p);
		return (1);
	}
	while (p->adjvex != j && p != NULL) {
		q = p;
		p = p->nextarc;
	}
	q->nextarc = p->nextarc;
	free(p);
	return (1);
}

int judgeconnect(ALGraph *G, InfoType vex1, InfoType vex2) {
	ArcNode *p;
	int k = LocateVex(G, vex1);
	int j = LocateVex(G, vex2);
	color[k] = 1;
	p = G->AdjList[k].firstarc;
	while (p != NULL) {
		if (p->adjvex == j) {
			flag = true;
			color[j] = 1;
			break;
		} else if (color[p->adjvex] != 1) {
			judgeconnect(G, G->AdjList[p->adjvex].data, vex2);
		}
		p = p->nextarc;
	}
	return 1;
}

int main() {
	int i;
	int c;
	VexType q, v;
	ALGraph G;
	memset(color, 0, sizeof(color));
	scanf("%d", &i);
	for (int k = 0; k < i; k++) {
		scanf("%d", &c);
		switch (c) {
			case 1:
				Create_Graph(&G);
				break;
			case 2:
				scanf("%d", &q);
				AddVertex(&G, q);
				break;
			case 3:
				scanf("%d%d", &q, &v);
				AddArc(&G, q, v);
				break;
			case 4:
				scanf("%d%d", &q, &v);
				DeleteArc(&G, q, v);
				break;
		}
	}
	scanf("%d%d", &q, &v);
	judgeconnect(&G, q, v);
	if (flag)
		printf("1");
	else
		printf("0");

	return 0;
}


