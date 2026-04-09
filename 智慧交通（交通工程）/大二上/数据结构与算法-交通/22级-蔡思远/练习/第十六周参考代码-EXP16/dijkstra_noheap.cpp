#include<cstdio>
#include<cstring>
#include<cmath>
#include<iostream>
#define MAXN 50001
#define MAXV 100000000
using namespace std;
struct Edge{
	int to;
	int v;
	Edge *next;
};


int n, m, size;
int dis[MAXN];
Edge *first[MAXN];
bool in_dis[MAXN];

void add_edge(int u, int v, int len)
{
	Edge* temp = new Edge;
	temp->to = v;
	temp->v = len;
	temp->next = first[u];
	first[u] = temp;
}

int get_min(){
	int min_num=MAXV, min_i=1;
	for(int i=1; i<=n; i++){
		if(!in_dis[i] && min_num >= dis[i]){
			min_i = i;
			min_num = dis[i];
		}
	}
	return min_i;
}

void dijkstra(){
	dis[1] = 0;
	while (size <= n){
		int min_i = get_min();
		size ++;
		in_dis[min_i] = true;
		Edge* temp = first[min_i];
		while (temp != NULL){
			if (dis[temp->to] > dis[min_i] + temp->v)
				dis[temp->to] = dis[min_i] + temp->v;
			temp = temp->next;
		} 
	}
}

void input_data()
{
	scanf("%d %d", &n, &m);
	for (int i = 1; i <= n; i++)
		dis[i]=MAXV;
	for (int i = 1; i <= m; i++) {
		int x, y, z;
		scanf("%d %d %d", &x, &y, &z);
		add_edge(x, y, z);
		add_edge(y, x, z);
	}

}

int main()
{
//	memset(dis, MAXV, sizeof(dis));
	input_data();
	dijkstra();
	for (int i = 2; i <= n; i++) 
	  printf("%d ", dis[i]);
	return 0;
}




