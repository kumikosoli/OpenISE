#include <stdio.h>
#include <stdlib.h>
#define MAX_VEX  100 /* 最大顶点数，应由用户定义 */
int color[MAX_VEX];
bool flag = false;

/* 定义节点结构体 */
struct Node {
	int from, to;              //起点和终点
	struct Node *in_pointer;   //指向入边的指针
	struct Node *out_pointer;  //指向出边的指针
};

/*  定义头结点结构体*/
struct head {
	int head_ele;
	struct Node *headin;
	struct Node *headout;
};

/* 定义十字链表结构体 */
struct Cross_List {
	int vex, edge;
	head list[MAX_VEX];
};

int LocateVex(Cross_List *G, int vp) {
	int  k;
	for (k = 1 ; k <= G->vex ; k++)
		if (G->list[k].head_ele == vp)
			return (k) ;
	return (-1) ;    /*  图中无此顶点  */
}

void *Create_Graph(Cross_List *G) {
	G->vex = 1 ;
	G->edge = 0;
	return (G);
}

int  AddVertex(Cross_List *G, int vp) {
	if  (G->vex >= MAX_VEX) {
//		printf("Vertex Overflow !\n") ;
		return (-1) ;
	}
	G->list[G->vex].head_ele = vp ;
	G->list[G->vex].headin = G->list[G->vex].headout = NULL ;
	return (++G->vex);
}

int  AddArc(Cross_List *G, int vex1, int vex2) {
	if (vex1 == vex2)
		return -1;
	Node *p;
	int k, j;
	p = (Node *)malloc(sizeof(Node));
	k = LocateVex(G, vex1);
	j = LocateVex(G, vex2);
	p->from = k;
	p->to = j;
	p->in_pointer = G->list[k].headin;   // 将起点的入边指针赋给新的边节点的入边指针
	p->out_pointer = G->list[j].headout; // 将终点的出边指针赋给新的边节点的出边指针
	G->list[k].headin = p;              // 将新的边节点赋给起点的入边
	G->list[j].headout = p;              // 将新的边节点赋给终点的出边
	return (1);
}

int judgeconnect(Cross_List *G, int vex1, int vex2) {
	Node *p;
	int k = LocateVex(G, vex1);
	int j = LocateVex(G, vex2);
	color[k] = 1;
	p = G->list[k].headin;
	while (p != NULL) {
		if (p->to == j) {
			flag = true;
			color[j] = 1;
			break;
		} else if (color[p->to] != 1) {
			judgeconnect(G, G->list[p->to].head_ele, vex2);
		}
		p = p->in_pointer;
	}
	return 1;
}

int main() {
	int i, c, q, v;
	Cross_List G;
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
