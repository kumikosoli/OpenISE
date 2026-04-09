#include<stdio.h>
#include <stdlib.h>
#include<algorithm>
#pragma warning(disable:4996)

const int MAX = 1000000000;

int N[10] = { 8,15,25,50,100,500,1000,2500,5000,12000};
int n;

FILE* fin;
char filename_in[10] = "0.in";

void makeData(int flag) {
	fprintf(fin, "%d\n", n);
	if (flag <= 5) {
		for (int i = 1; i <= n; i++) {
			int x= rand() % (2 * 3 * n + 1) - 3 * n;
			fprintf(fin, "%d ", x);
		}
	}
	else if(flag == 6 || flag == 7){
		for (int i = 1; i <= n; i++) {
			int x =rand() % (2 * 10 * n + 1)- 10 * n;
			fprintf(fin, "%d ", x);
		}
	}
	else if (flag == 8) {
		for (int i = 1; i <= n; i++) {
			int x = ((double)rand() / RAND_MAX) * 2 * MAX - MAX;
			fprintf(fin, "%d ", x);
		}
	}
	else for (int i = 1; i <= n; i++) fprintf(fin, "%d ", i + 100);
}

int main() {
	srand(0);
	for (int i = 0; i < 10; i++) {
		n = N[i];
		filename_in[0] = '0' + i;
		printf("producing %s...\n", filename_in);
		fin = fopen(filename_in, "w");
		makeData(i);
		fclose(fin);
	}
}
