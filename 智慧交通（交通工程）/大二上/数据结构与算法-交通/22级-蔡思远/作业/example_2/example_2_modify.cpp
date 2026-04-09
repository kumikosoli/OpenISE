#include <stdio.h>
#include <stdlib.h>
#include<string.h>
typedef int Status;
typedef char TElemType;

#define OK           1
#define FALSE        0
#define OVERFLOW    -2

typedef struct BiTNode {
    TElemType data;
    struct BiTNode *lchild, *rchild;
} BiTNode, *BiTree, *SElemType;

Status CreateBiTree(BiTree &T)
{
    char ch;
    scanf("%c", &ch);

    if('#' == ch) T = NULL;
    else{
        if(!(T = (BiTNode *)malloc(sizeof(BiTNode)))) exit(OVERFLOW);
        T->data = ch;             //Create the root node
//        printf("%c", T->data);
        CreateBiTree(T->lchild);  //Create left subtree
        CreateBiTree(T->rchild);  //Create right subtree
    }
    return OK;
}

Status InOrderTraverse(BiTree T)
{
	if(T == NULL)
        return OK;
    else{
    	InOrderTraverse(T->lchild);
    	printf("%c", T->data);
    	InOrderTraverse(T->rchild);
	}
	return OK;
} 

Status AfterOrderTraverse(BiTree T)
{
	if(T == NULL)
        return OK;
    else{
    	AfterOrderTraverse(T->lchild);
    	AfterOrderTraverse(T->rchild);
    	printf("%c", T->data);
	}
	return OK;
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
}
bool road(BiTree T,char s,char *a,int *index){
	if(T==NULL)return false;
	if(T->data==s){
		a[++(*index)]=T->data;
		return true;
	}
	//在左子树中查找 
	if(road(T->lchild,s,a,index)){
		a[++(*index)]=T->data;
		return true; 
	}
//在右子树中查找
	if(road(T->rchild,s,a,index)){

		a[++(*index)]=T->data;
		return true; 
	} 
	return false;
}


int main()
{
    BiTree T; char p;
    CreateBiTree(T);
    
    InOrderTraverse(T);
    printf("\n");
    AfterOrderTraverse(T);
    printf("\n");
    printf("%d\n", DeepTree(T)); 
    int index=-1;
    char s1;
    char a[100];
    scanf(" %c",&s1); 
    if ((road(T,s1,a,&index))) {
//    	printf("%s",a);
        printf("路径为：");
        
//        printf("%d ",index);
        for (int i =index;i>=0;i--) {
            printf("%c ",a[i]);
        }
    } 
	else {
        printf("未找到目标节点！");
    }
    return 0;
}
