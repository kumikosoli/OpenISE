#include<iostream>
#include<stdio.h>
#include<math.h>
#include<malloc.h>

using namespace std;
#define MAXQSIZE 100
int k=0;
char nodes[100];
//二叉树 
typedef struct BiNode{				
	char data;						//结点数据域
	struct BiNode *lchild,*rchild;	//左右孩子指针
}BiTNode,*BiTree;

//创建队列 
typedef struct{
    struct BiNode*  base[100];
    int front,rear;
}SqQueue;

//按先序次序创建二叉树T
void CreateBiTree(BiTree &T){	
	char ch;
	cin >> ch;
	if(ch=='#')  
		T=NULL;			//递归结束，建空树
	else
	{							
		T=(BiTree)malloc(sizeof(BiNode));
		T->data=ch;//生成根结点
		nodes[k++]=ch;// 记录所有结点信息 
		CreateBiTree(T->lchild);	//递归创建左子树
		CreateBiTree(T->rchild);	//递归创建右子树
	}							
}								

//先序遍历
void PreOrderTraverse(BiTree T){
	if(T)
	{
		printf("%c ",T->data);
		PreOrderTraverse(T->lchild);
		PreOrderTraverse(T->rchild); 
	}
}
 
//中序遍历							
void InOrderTraverse(BiTree T){  
	if(T){
		InOrderTraverse(T->lchild);
		printf("%c ",T->data);
		InOrderTraverse(T->rchild);
	}
}

//后序遍历 
void PostOrderTraverse(BiTree T){
	if(T)
	{
		PostOrderTraverse(T->lchild);
		PostOrderTraverse(T->rchild);
		printf("%c ",T->data);
	}
}

//求给定结点的路径
void FindPath(BiTree root,char ch){    
    typedef struct{
 		BiTree t;
 		int tag;//tag=0表示访问左子树，tag=1表示访问右子树
 	}stack;
 	
    stack s[100];
	int top=0,flag=0,i,j=0;
	
	// 检验搜索的结点是否唯一 
	for(i=0;i<=k;i++)
		if(nodes[i]==ch)
			j++;
	if(j>1)
	{
		printf("此结点不唯一！\n");
		return;
	}
	
	while(root||top)
 	{
 		// 遍历所有左子树并存入栈，直到找到目标结点或到达叶子结点 
  		while(root&&root->data!=ch)
  		{
   			s[++top].t=root;
			s[top].tag=0;
			root=root->lchild;//访问左子树
  		}
  		
  		if(root&&root->data==ch)
  		{
   			printf("从根节点到达结点%c的路径为：",ch);
   			for(int i=1;i<=top;i++)
				printf("%c",s[i].t->data);
			flag=1;
			printf("%c\n",ch);
			return ;
  		}
  		
  		// 依次访问先前存入的左子树的右子树 
  		while(top&&s[top].tag==1)
  			top--;//退栈
  		if(top)
  		{
   			s[top].tag=1;
			root=s[top].t->rchild;//访问右子树
  		}
 	}
 	if(flag==0)
 		printf("不存在此结点！\n\n"); 
 	return;
}

int DeepTree(BiTree T)
{
	 if(T == NULL)
        return 0;

    int ldeep, rdeep, deep = 0;
    ldeep = DeepTree(T->lchild);
    rdeep = DeepTree(T->rchild);
    deep = (ldeep > rdeep ? ldeep : rdeep);

    return (deep + 1);

    //please finish the following parts
}

int main(){
	BiTree tree;
	int p=-1;
	char node;
	
				CreateBiTree(tree);
				printf("先序遍历为："); 
				PreOrderTraverse(tree);
				printf("\n\n");
				
				printf("中序遍历为：");
				InOrderTraverse(tree);
				printf("\n\n");
	
				printf("后序遍历为：");
				PostOrderTraverse(tree);
				printf("\n\n");

				printf("该二叉树的深度为：");
			    printf("%d\n", DeepTree(tree));
				printf("请输入搜索结点名称:\n");
				cin >> node;
				FindPath(tree,node); 
		
				
		
	return 0;
}

