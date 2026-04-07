#include "stdio.h"
#include "stdlib.h"
typedef struct node{
	int data;
	struct node *prior, *next;
}JD;
int main() 
{
	JD *h,*s;
	int i;
	h=(JD*)malloc(sizeof(JD));
	h->data=0;
	h->prior=h;
	h->next=h;
	for(i=10;i>0;i--){
		s=(JD*)malloc(sizeof(JD));
		s->data=i*i;
		s->prior=h;
		s->next=h->next;
		h->next->prior=s;
		h->next=s;
	}
//	h->prior=s;
//	s->next=h;
	s=h;
	for(i=0;i<=20;i++){
	printf("%d\n",s->data);
	s=s->next;
	}
	s=h;
		for(i=0;i<=20;i++){
	printf("%d\n",s->data);
	s=s->prior;
	}
	
}
