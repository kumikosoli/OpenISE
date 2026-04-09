#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#define MAX_VEX  100
typedef int VexType;
typedef int InfoType;

bool flag = false;
int color[MAX_VEX];

typedef struct ArcNode {
	int adjvex;
	struct 	ArcNode *nextarc;
} ArcNode;

typedef struct {
	int data;
	int degree;
	ArcNode *firstarc;
} AdjList;

typedef struct {
	char kind;
	int vexnum, arcnum; 
	AdjList AdjList[MAX_VEX]; 
} ALGraph;

ALGraph *Create_Graph(ALGraph *G) {
	G->vexnum = 0 ;
	return (G) ;
}

int LocateVex(ALGraph *G, VexType vp) {
	int  k;
	for (k = 0 ; k < G->vexnum ; k++)
		if (G->AdjList[k].data == vp)
			return (k) ;
	return (-1) ;    /*  ͼ���޴˶���  */
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
	q->nextarc = NULL;

	q->nextarc = G->AdjList[k].firstarc;
	G->AdjList[k].firstarc = q;
	return (1);
}

int  DeleteArc(ALGraph *G, InfoType vex1, InfoType vex2) {
	ArcNode *p, *q ;
	if (vex1 == vex2)
		return (-1);
	int k = LocateVex(G, vex1)  ;
	int j = LocateVex(G, vex2)  ;
	if (k == -1 || j == -1) {
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


