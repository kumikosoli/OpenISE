#include <iostream>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int Heap[10001];//从1开始计数 
int size; //heap size 


//insert val to heap 
void insert(int val) {
  int i = ++size;
   //please finish the following parts
  while (  ){ //finish this bracket
 

  }
  Heap[i] = val;
}

//delete_min 
int delete_min() {
  int val = Heap[size--], ret = Heap[1];
  int i = 1, ch = 2;
  // please finish the following parts
  while (    ){//finish this bracket
    
    
    
  }
  Heap[i] = val; 
  return ret;
}

void delete_i(int i) {
  int val = Heap[size--], ch = i * 2;
  
  //please finish the following parts 
  while (){//finish this bracket

   

  }
  
   //please finish the following parts 
  while (){//finish this bracket
  
  
  }
  Heap[i] = val;
}


void decrease_value(int i, int val) {
	
  //please finish the following parts 
  while (){
 
  }
  Heap[i] = val;
}



int main(int argc, char** argv) {
	size = 0;
	int k=0,m,order,x,i;
	scanf("%d",&m);
	for (k=0;k<m;k++){
		scanf("%d",&order);
		switch(order){
			case 1:scanf("%d",&x);insert(x);break;
			case 2: delete_min() ;break;
			case 3:scanf("%d",&x);delete_i(x);break;
			case 4:scanf("%d",&i);scanf("%d",&x);decrease_value(i, x);break;
		}
    } 

    while(size!=0){
    	printf("%d ",delete_min());
	}   	
	return 0;
}
