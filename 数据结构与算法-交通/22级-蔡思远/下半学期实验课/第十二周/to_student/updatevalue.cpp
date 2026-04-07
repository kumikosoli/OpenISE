#include <iostream>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int Heap[10001];//从1开始计数 
int size; //heap size 


//insert val to heap 
void insert(int val) {
  
}

//delete_min 
int delete_min() {
  
}

void update_value(int i, int val){
	
} 

int main(int argc, char** argv) {
	size = 0;
	int k=0,m,order,x,i;
	scanf("%d",&m);
	for (k=0;k<m;k++){
		scanf("%d",&order);
		switch(order){
			case 1:scanf("%d",&x);insert(x);break;
			case 2:scanf("%d",&i);scanf("%d",&x);update_value(i, x);break;
		}
    } 

    while(size!=0){
    	printf("%d ",delete_min());
	}   	
	return 0;
}
