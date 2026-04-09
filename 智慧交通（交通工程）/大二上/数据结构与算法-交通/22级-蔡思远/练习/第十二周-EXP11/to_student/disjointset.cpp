#include <stdio.h>
#include <stdlib.h>
#define MAXN 7000000
int fa[MAXN], rank[MAXN];
int find(int x)
{
	
        //please finish the following parts
		
}
void merge(int i, int j)
{
    
    //please finish the following parts

}
int main()
{
     int T,n,m,u,v,i,sum;
     sum=0;
     scanf("%d%d",&n,&m);
     for(i=1;i<=n;i++)
     {
         //please finish the following parts ³õÊ¼»¯ 

      }
     for(i=0;i<=m-1;i++)
     {
         scanf("%d%d",&u,&v);
         merge(u,v);
         }
     for(i=1;i<=n;i++)
     {
         if(fa[i]==i)
         {
               //please finish the following parts

             }
         }
     printf("%d\n",sum);
     return 0;
}

