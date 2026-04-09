#include <stdio.h> 
#define M 50
typedef struct node{   
	int i,j;
	int v;
}JD;
JD ma[M], mb[M];

int trans_sparmat(JD ma[],JD mb[]){
	int col, p, n, t, k;
	if(ma[0].v==0)
    	return(0);
	n=ma[0].j;
	t=ma[0].v;
	mb[0].i=n;  mb[0].j=ma[0].i; mb[0].v=t;
	k=1;
	for(col=1;col<=n;col++)
		for(p=1;p<=t;p++)
			if(ma[p].j==col){
				mb[k].i=ma[p].j;
				mb[k].j=ma[p].i;
				mb[k].v=ma[p].v;
				k++;
			}
	return(1);
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
