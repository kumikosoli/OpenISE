#include<stdio.h>
#include<stdlib.h>
const int maxn=10000001;
int A[maxn+1];
int L[maxn],R[maxn];
int count;
char infilename[10]="0.in";
char outfilename[10]="0.out";
FILE * fin, * fout;

void merge(int arr[],int left,int middle,int right){
	int i,j;
	int n1=middle-left+1;
	int n2=right-middle;
	//int L[maxn],R[maxn];
	for(i=0;i<n1;i++) L[i]=arr[left+i];
	for(j=0;j<n2;j++) R[j]=arr[middle+1+j];
	i=0;
	j=0;
	int k=left;
	while(i<n1 && j<n2){
		if(L[i]<=R[j]) arr[k++]=L[i++];
		else{arr[k++]=R[j++];
			count = count+n1-i;
		}
	}
	while(i<n1) arr[k++]=L[i++];
	while(j<n2) arr[k++]=R[j++]; 
}

void mergesort(int arr[],int left, int right){
	if(left<right){
		int middle=left+(right-left)/2;
		mergesort(arr,left,middle);
		mergesort(arr,middle+1,right);
		merge(arr,left,middle,right);
	}
}

void print_arr(int count){
	fprintf(fout,"%d",count);
	fclose(fout);
}

 int main()
 {
 	int m;
	for(int t=0;t<10;t++){
		printf("%d", t);
		count = 0;
	    infilename[0] = '0' + t;
		outfilename[0] = '0' + t;
		fin = fopen(infilename, "r");
	    fout = fopen(outfilename, "w");
		fscanf(fin, "%d", &m);
		for(int i=0;i<m;i++) fscanf(fin,"%d",&A[i]);
		mergesort(A,0,m-1);
		print_arr(count);
		fclose(fin);
	}
	return 0;
} 
