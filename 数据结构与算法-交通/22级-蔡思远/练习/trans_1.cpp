#include <stdio.h> 
#define M 50
typedef struct node{   
	int i,j;
	int v;
}JD;
JD ma[M], mb[M];

int trans_sparmat(JD ma[],JD mb[]){
	
}

int main(){
	int k;
	scanf("%d %d %d", &ma[0].i, &ma[0].j, &ma[0].v);
	for (k=1; k<=ma[0].v; k++)
		scanf("%d %d %d", &ma[k].i, &ma[k].j, &ma[k].v);
	trans_sparmat(ma, mb);
	for (k=0; k<=mb[0].v; k++)
		printf("%d %d %d\n", mb[k].i, mb[k].j, mb[k].v);
	return 0;
}
