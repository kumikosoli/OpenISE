#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <sys/time.h>
char inputfilename[12] = "0.in";
char outputfilename[12] = "0.out";
FILE * fin;
FILE * fout;
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int Heap[10001];//从1开始计数 
int size; //heap size 


//insert val to heap 
void insert(int val) {
  int i = ++size;
  while (i > 1 &&  val < Heap[i/2]){
    Heap[i] = Heap[i/2];
    i /= 2;
  }
  Heap[i] = val;
}

//delete_min 
int delete_min() {
  int val = Heap[size--], ret = Heap[1];
  int i = 1, ch = 2;
  while (ch <= size){
    if (ch < size && Heap[ch+1] < Heap[ch]) 
        ch++;
    if (val <= Heap[ch]) break;
    Heap[i] = Heap[ch]; i = ch; ch += ch;
  }
  Heap[i] = val; 
  return ret;
}

//
void update_value(int i, int val){
	int ch = i*2;
  	while (ch <= size){
    	if (ch < size && Heap[ch+1] < Heap[ch])   ch++;
    	if (val <= Heap[ch]) break;
    	Heap[i] = Heap[ch]; i = ch; ch += ch;
  	}
  	while (i > 1 && val < Heap[i / 2]){
    	Heap[i] = Heap[i / 2];
		i /= 2;
  	}
  	Heap[i] = val;
} 

int main(int argc, char** argv) {
	
	int i =0;
	for (i=0;i<10;i++){
		inputfilename[0] = '0' + i;
        outputfilename[0] = '0' + i;
		size = 0;
		int k,m,order,x,p;
		scanf("%d",&m);
		fin = fopen(inputfilename, "w");
	    fprintf(fin,"%d\n",m);
		
		for (k=0;k<m;k++){
			if (size<=1 )
			     order = 1;
			else
			    order= rand()%2+1;
			
			switch(order){
				case 1:fprintf(fin,"%d ",order);x= rand()%10000;fprintf(fin,"%d\n",x);;insert(x);break;
				case 2:fprintf(fin,"%d ",order);p=rand()%size+1;x=rand()%10000;fprintf(fin,"%d ",p);fprintf(fin,"%d\n",x);update_value(p, x);break;
			}
		} 
		fclose(fin);
		
		fout = fopen(outputfilename, "w");
		while(size!=0){			
			fprintf(fout,"%d ",delete_min());
			//printf("%d ",delete_min());	
		} 
		fclose(fout);
	}
	  	
	return 0;
}
