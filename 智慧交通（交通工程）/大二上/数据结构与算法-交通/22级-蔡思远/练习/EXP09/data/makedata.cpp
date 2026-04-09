#include<stdio.h>
#include<stdlib.h>

const int maxn=1000001;
int A[maxn];
char filename[10] = "0.in";
const int N[10]={10,15,30,50,699,2000,30000,500000,500000,1000000};

void swap(int &a,int &b) {
	int c;
	c = a; a = b; b = c;
}

void getrandom1(int n){
	for(int i=0;i<n;i++){
		A[i]=rand()%41-20; 
	}
}
void getrandom2(int n){
	for(int i=0;i<n;i++){
		A[i]=rand()%101-50; 
	}
}
void getrandom3(int n){
	for(int i=0;i<n;i++){
		A[i]=rand()%201-100; 
	}
}
void getrandom4(int n){
	for(int i=0;i<n;i++){
		A[i]=rand()%4001-2000; 
	}
}
void getrandom5(int n){
	for(int i=0;i<n;i++){
		A[i]=rand()%10001-5000; 
	}
}
void getrandom6(int n){
	for(int i=0;i<n;i++){
		A[i]=-1000000000+int(2000000000.0*rand()/RAND_MAX);
	}
}
int cmpfunc1(const void*_a,const void*_b){  
	int *a=(int*)_a;
	int *b=(int*)_b;
	return *a-*b;
}


void getarr(int n) //生成排好序的点 
{
	for(int i=0;i<n;i++) A[i]=-1000000000+int(2000000000.0*rand()/RAND_MAX);
	qsort(A,n,sizeof(A[0]),cmpfunc1);
}

int cmpfunc2(const void*_a,const void*_b){
	int *a=(int*)_a;
	int *b=(int*)_b;
	return *b-*a;
}
void getrearr(int n)// 生成逆序输出的点
{
	for(int i=0;i<n;i++) A[i]=-1000000000+int(2000000000.0*rand()/RAND_MAX);
	qsort(A,n,sizeof(A[0]),cmpfunc2);
} 
void print_arr(int n){
	FILE* fout = fopen(filename, "w");
	fprintf(fout,"%d\n",n);
	for(int i=0;i<n;i++) fprintf(fout,"%d ",A[i]);
	fclose(fout);
} 

int main()
{
	srand(0);
	for(int t=0;t<10;t++){
		int n=N[t];
		filename[0] = '0' + t;
		printf("producing %s...\n", filename);
		if(t==0){
			getrandom1(n);
			print_arr(n);
		}
		else if(t==1){
			getrandom2(n);
			print_arr(n);
		}
		else if(t==2){
			getrandom3(n);
			print_arr(n); 
		}
		else if(t==3){
			getrandom4(n);
			print_arr(n); 
		}
		else if(t==4){
			getrandom5(n);
			print_arr(n);
		}
		else if(t==7){
			getarr(n);
			print_arr(n);
		}
		else if(t==8){
			getrearr(n);
			print_arr(n);
		}
		else{
			getrandom6(n);
			print_arr(n);
		}
	}
	return 0;
}
