#include <stdio.h> 
#define M 50
typedef struct node{   
	int i,j;
    int v;
}JD;
JD ma[M], mb[M];

int fast_transpos(JD ma[], JD mb[]){
	int n, col, p, k, t;
	int num[M], cpot[M];
	n = ma[0].j;
	t = ma[0].v;
	mb[0].i = n;  mb[0].j = ma[0].i;  mb[0].v = t;
	if(t <= 0)
		return(0);
	for(col=0; col<=n; col++)
    	num[col] = 0;
	for(p=1; p<=t; p++){
		k = ma[p].j;
    	num[k]++;
	}
	cpot[0] = 0; cpot[1] = 1;
	for(col=2; col<=n; col++)
		cpot[col] = cpot[col-1] + num[col-1];
	for(p=1; p<=t; p++){
		col = ma[p].j;
    	k = cpot[col];
    	mb[k].i = ma[p].j;
    	mb[k].j = ma[p].i;
    	mb[k].v = ma[p].v;
    	cpot[col]++;
	}
	return(1);
}

int main(){
	int k;
	scanf("%d %d %d", &ma[0].i, &ma[0].j, &ma[0].v);
	for (k=1; k<=ma[0].v; k++)
		scanf("%d %d %d", &ma[k].i, &ma[k].j, &ma[k].v);
	fast_transpos(ma, mb);
	for (k=0; k<=mb[0].v; k++)
		printf("%d %d %d\n", mb[k].i, mb[k].j, mb[k].v);
	return 0;
}
