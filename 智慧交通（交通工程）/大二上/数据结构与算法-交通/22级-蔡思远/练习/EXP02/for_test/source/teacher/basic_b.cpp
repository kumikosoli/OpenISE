#include <stdio.h>
#include <stdlib.h>

int m;  //命令数

struct node{
	int data;
	struct node *next;
};
node *head; // headָ指向头结点

//插入x到a[i]
void insert(int i, int x){
	node *p = head;
	while (i > 1){
		p = p->next; i--;
	} 
	node *q = (node*) malloc(sizeof(node));
	q->data = x; q->next = p->next; p->next = q;	
} 

//删除a[i]
void deleteByIndex(int i){
	node *p = head;
	node *q = head->next;
	while (i > 1){
		p = q; q = p->next; i--;
	}
	p->next = q->next;
	free(q);
} 

//查找第一个x
void find(int x){
	node *p = head->next; 
	int j = 1;
	while (p != NULL && p->data != x){
		p = p->next; j++;
	}
	if (p == NULL) j = 0;
	printf("%d\n", j);
}

//统计[x,y]中元素个数
void count(int x, int y){
	int k = 0;
	node *p = head->next; 
	while (p != NULL){
		if (p->data >= x && p->data <= y) k++;
		p = p->next;
	}
	printf("%d\n", k);
}

//去除[x,y]范围内的元素
void deleteByRange(int x, int y){
	node *p = head;
	node *q = head-> next;
	while (q != NULL){
		if (q->data >= x && q->data <= y){
			p->next = q->next; free(q); q = p->next;
		}
		else{
			p = q; q = p->next;
		}
	}
} 

//去除重复元素
void eliminateRepeat(){
	node *r = head->next, *p, *q;
	while (r != NULL){
		p = r; q = r->next;
		while (q != NULL){
			if (q->data == r->data){
				p->next = q->next; free(q);	q = p->next;
			}
			else{
				p = q; q = p->next;
			}
		}
		r = r->next;
	}
}

int main() {
	scanf("%d", &m);
	head = (node*) malloc(sizeof(node));
	head->next = NULL;
	for (int k = 0; k < m; k++){
		int c, i, x, y;
		scanf("%d", &c);
		switch (c){
			case 1: scanf("%d%d", &i, &x); insert(i, x); break;
			case 2: scanf("%d", &i); deleteByIndex(i); break;
			case 3: scanf("%d", &x); find(x); break;
			case 4: scanf("%d%d", &x, &y); count(x, y); break;
			case 5: eliminateRepeat(); break;
			case 6: scanf("%d%d", &x, &y); deleteByRange(x, y); break;
		}
	}
	//fclose(fin); fclose(fout);
	return 0;
}

