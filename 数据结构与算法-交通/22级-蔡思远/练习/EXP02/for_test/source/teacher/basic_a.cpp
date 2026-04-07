#include <stdio.h>

const int maxn = 10000;

int m;  //命令数
int n;  //线性表中元素个数
int arr[maxn];

/*const char * inputfilename =  "9.in";
const char * outputfilename = "9.out";
FILE * fin = fopen(inputfilename, "r");
FILE * fout = fopen(outputfilename, "w"); */

//插入x到a[i]
void insert(int i, int x){ 
	for (int j = n; j >= i; j--)
		arr[j] = arr[j - 1];
	arr[i - 1] = x;
	n++;
} 
////
//删除a[i]
void deleteByIndex(int i){ 
	for (int j = i; j < n; j++)
		arr[j - 1] = arr[j];
	n--;
} 

//查找第一个x
void find(int x){ 
	for (int j = 0; j < n; j++)
		if (arr[j] == x){
			printf("%d\n", j + 1);
			return;
		}
	printf("0\n");
}

//统计[x,y]中元素个数
void count(int x, int y){
	int k = 0;
	for (int j = 0; j < n; j++)
		if (arr[j] >= x && arr[j] <= y)
			k++;
	printf("%d\n", k);
}

//去除[x,y]范围内的元素
void deleteByRange(int x, int y){
	int k = 0;
	for (int j = 0; j < n; j++)
		if (arr[j] < x || arr[j] > y)
			arr[k++] = arr[j];
	n = k;
} 

//去除重复元素
void eliminateRepeat(){
	int i = 0;
	while (i < n){
		int k = i + 1;
		for (int j = i + 1; j < n; j++)
			if (arr[j] != arr[i])
				arr[k++] = arr[j];
		n = k; i++;
	}
}
////
int main() {
	scanf("%d", &m);
	for (int k = 0; k < m; k++){
		int c, i, x, y;
		scanf("%d", &c);
		switch (c){
			case 1: scanf("%d%d", &i, &x); insert(i, x); break;
			case 2: scanf("%d", &i); deleteByIndex(i); break;
			case 3: scanf("%d", &x); find(x); break;
			case 4: scanf("%d%d", &x, &y); count(x, y); break;
			case 5: eliminateRepeat(); break;
			case 6: scanf("%d%d", &x, &y); deleteByRange(x, y); break;
		}
	}
	/*fclose(fin); fclose(fout);*/
	return 0;
}
