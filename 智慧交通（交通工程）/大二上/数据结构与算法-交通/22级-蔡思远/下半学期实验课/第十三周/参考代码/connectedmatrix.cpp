#include<stdio.h>
#include<memory.h>
const int maxn=401;
int edge[maxn][maxn], color[maxn];
bool flag=false;
int n;

void judgeconnect(int u,int v){
	color[u]=1;
	if(u<1 || u>n || v<1 || v>n) return;
	if (edge[u][v]==1){
		color[v]=1;
		flag=true;
		return;
	}
	for(int i=1;i<=n;i++)//遍历与u点相连的点
		if(edge[u][i]==1 && color[i]==0) judgeconnect(i, v);
	return;
}

int main(){
	int q, k;
    scanf("%d",&n);
    memset(edge,0,sizeof(edge));
    memset(color,0,sizeof(color));
    for(int i=1;i<=n;i++)
    	for(int j=1;j<=n;j++)
    		scanf("%d",&edge[i][j]);
	scanf("%d %d",&q, &k);
	judgeconnect(q, k);
	if(flag) printf("1");
	else printf("0");
	return 0;
}
