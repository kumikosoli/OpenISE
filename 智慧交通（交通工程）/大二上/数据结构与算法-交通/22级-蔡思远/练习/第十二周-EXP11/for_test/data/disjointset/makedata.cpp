//
// Created by Wsin on 2021/03/18.
//
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/time.h>
  

char inputfilename[12] = "0.in";
char outputfilename[12] = "0.out";
FILE * fin;
FILE * fout;
#define MAXN 7000000
int fa[MAXN], rank[MAXN];

//using namespace std;
int find(int x)
{
    return x == fa[x] ? x : (fa[x] = find(fa[x]));
}
inline void merge(int i, int j)
{
    int x = find(i), y = find(j);
    if (rank[x] <= rank[y])
        fa[x] = y;
    else
        fa[y] = x;
    if (rank[x] == rank[y] && x != y)
        rank[y]++;
}


int main(int argc, char* argv[]) {
    int data[]={10,100,1000,10000,100000,200000,300000,400000,500000,2000000};
    int num;
    int edge;
    int e1,e2;
    int sum;
    int index1;
    int index2;
    for (int i = 0; i < 10; i++) {
    	sum=0;
    	inputfilename[0] = '0' + i;
        outputfilename[0] = '0' + i;
        num=data[i];
        fin = fopen(inputfilename, "w");
        fout = fopen(outputfilename, "w");
	    struct timespec time1 = { 0, 0 };
	    clock_gettime(CLOCK_REALTIME, &time1);
	    srand(time1.tv_nsec);        
		for(int j=1;j<=num;j++){
	         fa[j]=j;
	   	}
        
        edge=rand()%(num*(num-1)/4)+num;
    	fprintf(fin,"%d %d\n",num,edge);
		for(int j=0;j<edge;j++){
			e1=rand()%num+1;
			e2=rand()%num+1;
			while(e1==e2){
				e1=rand()%num+1;
				e2=rand()%num+1;			
			}
			fprintf(fin,"%d %d\n",e1,e2);
			merge(e1,e2);
		} 
		for(int j=1;j<=num;j++){
	     	if(fa[j]==j){
	         sum++;
	        }
	    }
	    fclose(fin);
	    fprintf(fout,"%d\n",sum);
	    fclose(fout);
    }
    return 0;
}

