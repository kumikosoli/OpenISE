#include <stdio.h>
#include <stdlib.h>

struct node{
	int data;
	struct node *prior;
	struct node *next;
};
node *head; // headָ指向头结点

//建立一个长度为n的双向循环链表，元素值分别为1、4、9、……、n^2
//方法：依次插入n个元素，元素值为i^2(i=1,2,3,……,n)
void build(int n){
	node *p = head;
	for (int i = 1; i <= n; i++){
		node *q = (node*) malloc(sizeof(node));
		q->data = i*i; q->prior = p; q->next = p->next; p->next = q;
		p = p->next;
	} 
	p->next = head; head->prior = p;
} 

//插入值为a的元素，并保持链表元素的排序
void insert(int a){
	node *p = head->next;
	while (p != head){ //判断a是否小于链表中的最小值，若是，则插入到链表最前端
		if (head->next->data > a){
			node *q = (node*) malloc(sizeof(node));
			q->data = a; q->next = p; q->prior = head; p->prior->next = q; p->prior = q;
			break;
		}
		else if ((p->data <= a && p->next->data > a) || (p->next == head)){
			node *q = (node*) malloc(sizeof(node));
			q->data = a; q->next = p->next; q->prior = p; p->next->prior = q; p->next = q;
			break;
		} 
		p = p->next;
	}
} 

//删除元素值为a的节点
void deleteByValue(int a){
	node *p = head->next;
	while (p != head){
		if (p->data == a){
			p->prior->next = p->next;
			p->next->prior = p->prior;
			free(p);
			break;
		} 
		else p = p->next;
	}
} 

//从头到尾读取链表（正序读取）
void read_positive(node *head){
	node *p = head->next;
	while (p != head){
		printf("%d ", p->data);
		p = p->next;
	}
	printf("\n");
} 

//从尾到头读取链表（逆序读取）
void read_reverse(node *head){
	node *p = head->prior;
	while (p != head){
		printf("%d ", p->data);
		p = p->prior;
	}
	printf("\n");
} 

int main() {
	int n, a, b;
	head = (node*) malloc(sizeof(node));
	head->next = NULL;
	head->prior = NULL;
	scanf("%d", &n); build(n);
	scanf("%d", &a); deleteByValue(a);
	scanf("%d", &b); insert(b);
	read_positive(head);
	read_reverse(head);
	return 0;
}
