#include<stdio.h>

const int maxn = 100000;
const int maxm = 500000;

int edge[maxm + 1][3];
int point[maxm + 1];
int ind[maxm + 1]; 
int m, n;

void swap(int &a, int &b) {
	int tmp = a; a = b; b = tmp;
}

int partition(int l, int r) {
	int i = l;
	for (int j = l; j < r; j++) 
		if (edge[ind[j]][2] < edge[ind[r]][2])
		swap(ind[j],ind[i++]);
	swap(ind[i],ind[r]);
	return i;
}

void Qsort(int l, int r) {
	if(l<r)
	{
		int k = partition(l, r);
		Qsort(l,k-1);
		Qsort(k+1,r);
	};
}

int kruskal() {
    int sumCost = 0;
    for (int i = 1; i <= n; i++) {
        point[i] = i;
    }

    for (int i = 1; i <= m; i++) {
        if (point[edge[ind[i]][0]] != point[edge[ind[i]][1]]) {
            
            int start = point[edge[ind[i]][0]];
            int end = point[edge[ind[i]][1]];
            sumCost += edge[ind[i]][2];
            for (int j = 1; j <= n; j++) {
                if (point[j] == end) {
                    point[j] = start;
                }
            }
            int flag = 0;
            for (int j = 1; j <= n; j++) {
                if (point[j] != start) {
                    flag = 1;
                    break;
                }
            }
            if (flag == 0) {
                break;
            }
        }
    }
    return sumCost;
}


int main() {
	scanf("%d %d", &n, &m);
	for (int i = 1; i <= m; i++) 
		scanf("%d %d %d", &edge[i][0], &edge[i][1], &edge[i][2]);
    for (int i = 1; i <= m; i++) ind[i] = i;
	Qsort(1, m);
	int res = kruskal();
	printf("%d", res);
	return 0;
}
