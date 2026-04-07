#include<stdio.h>
#include<stdlib.h>
const int maxn=10000001;
int A[maxn+1];
int L[maxn],R[maxn];
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
		if(L[i]<=R[j]) arr[k]=L[i++];
		else  arr[k]=R[j++];
		k++; 
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

void print_arr(int arr[],int size){
	for(int i=0;i<size;i++) fprintf(fout,"%d ",arr[i]);
	fclose(fout);
}

 int main()
 {
 	int m;
	for(int t=0;t<10;t++){
		printf("%d", t);
	    infilename[0] = '0' + t;
		outfilename[0] = '0' + t;
		fin = fopen(infilename, "r");
	    fout = fopen(outfilename, "w");
		fscanf(fin, "%d", &m);
		for(int i=0;i<m;i++) fscanf(fin,"%d",&A[i]);
		mergesort(A,0,m-1);
		print_arr(A,m);
		fclose(fin);
	}
	return 0;
} 
