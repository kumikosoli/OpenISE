#include<stdio.h>
#include<stdlib.h>
#define MAXN 10001
#define TRUE 1
#define FALSE 0

typedef int TElemType;
typedef struct BiTNode {
    TElemType data;
    struct BiTNode *lchild, *rchild; 
} BiTNode, *BiTree;

BiTree T;
int top;
TElemType path[MAXN];
int nodenum, depth=1;
float asl;

int SearchBST(BiTree T, TElemType key, BiTree f, BiTree &p){
	if(!T) {p = f; return FALSE;}
	else if(key==T->data){
		p = T;
		path[top++] = T->data;
		return TRUE;
	}
	else if(key<T->data){
		path[top++] = T->data;
		SearchBST(T->lchild, key, T, p);
	}
	else{
		path[top++] = T->data;
		SearchBST(T->rchild, key, T, p);
	}
}

int InsertBST(BiTree &T, TElemType e){
	BiTree p;
	if(!SearchBST(T, e, NULL, p)){
		BiTree s = (BiTree)malloc(sizeof(BiTNode));
		s->data = e;  
		s->lchild = s->rchild = NULL;
		if(!p)  T = s;
		else if (e<p->data)  p->lchild = s;
		else  p->rchild = s; 
	}
	else return FALSE;
}

void Delete(BiTree &p){
	BiTree q, s;
	if (!p->rchild)  {q = p; p = p->lchild; free(q);} 
    else if (!p->lchild) {q = p; p = p->rchild; free(q);} 
    else {
    	q = p; s = p->lchild;
		while(s->rchild) {q = s;  s = s->rchild;}
		p->data = s->data;
		if (q != p )  q->rchild = s->lchild;             
		else  q->lchild = s->lchild;
		free(s);
	}
}

int DeleteBST(BiTree &T, TElemType key){
	if(!T)  return FALSE;
	else{
		if(key==T->data){
			Delete(T);
			return TRUE;  
		}
		else if(key<T->data) DeleteBST(T->lchild, key);
		else  DeleteBST(T->rchild, key);
	}
}

void CalAsl(BiTree T){
	if (T){
		asl += depth;
		nodenum ++;
		depth ++;
		CalAsl(T->lchild);
		CalAsl(T->rchild);
		depth --;
	}
}

int main(){
	int m, c, x;
	scanf("%d", &m);
	for(int i=1; i<=m; i++){
		scanf("%d", &c);
		switch(c){
			case 1: {scanf("%d", &x); InsertBST(T, x); break;}
			case 2: {scanf("%d", &x); DeleteBST(T, x); break;}
			case 3: {
				BiTree p; top = 0;
				scanf("%d", &x);
				SearchBST(T, x, NULL, p);
				for(int i=0; i<=top-1; i++) printf("%d ", path[i]);
				printf("\n"); break;
			}
		}
	}
	CalAsl(T);
	printf("%.2f\n", asl/nodenum);
	return 0;
}
