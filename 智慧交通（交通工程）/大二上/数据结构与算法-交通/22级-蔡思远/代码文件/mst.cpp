#include <stdio.h>

const int maxn = 100000;
const int maxm = 500000;

int edge[maxm + 1][3];
int parent[maxn + 1];
int rank[maxn + 1];
int ind[maxm + 1]; 
int m, n;

int Find(int x) { 
	if (x != parent[x])  parent[x] = Find(parent[x]);
	return parent[x];
}

void Union(int r, int s) { 
	if (rank[s] > rank[r]) parent[r] = s;
	else if (rank[s] < rank[r]) parent[s] = r;
	else { parent[s] = r; rank[r]++; }
}

void swap(int &a, int &b) {
	int tmp = a; 
	a = b; 
	b = tmp;
}

int partition(int l, int r) {
	int i = l;
	for (int j = l; j < r; j++){ 
		if (edge[ind[j]][2] < edge[ind[r]][2]){
			swap(ind[j],ind[i++]);}
			}
	swap(ind[i],ind[r]);
	return i;
}

void Qsort(int l, int r) {
	if(l < r) {
		int k = partition(l, r);
		Qsort(l, k-1);
		Qsort(k+1, r);
	}
}

int kruskal() {
	for (int i = 1; i <= n; i++) { 
		parent[i] = i; 
		rank[i] = 0;
	}
	int sumCost = 0, cnt = 0;
	for (int i = 1; i <= m; i++) {
		int vexa=Find(edge[ind[i]][0]), vexb=Find(edge[ind[i]][1]);
		if(vexa!=vexb) {
			Union(vexa,vexb);
			cnt++;
			sumCost += edge[ind[i]][2];
		}
	}
	if (cnt != n - 1) printf("some thing is wrong");
	return sumCost;
}

int main() {
	scanf("%d %d", &n, &m);
	for (int i = 1; i <= m; i++) scanf("%d %d %d", &edge[i][0], &edge[i][1], &edge[i][2]);
	for (int i = 1; i <= m; i++) ind[i] = i;
	Qsort(1, m);  
	int res = kruskal();
	printf("%d", res);
	return 0;
}
