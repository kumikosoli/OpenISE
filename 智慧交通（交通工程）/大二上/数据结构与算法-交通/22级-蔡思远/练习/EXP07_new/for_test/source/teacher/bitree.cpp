#include <stdio.h>
#include <stdlib.h>

typedef int Status;
typedef char TElemType;

#define OK           1
#define FALSE        0
#define OVERFLOW    -2

typedef struct BiTNode {
    TElemType data;
    struct BiTNode *lchild, *rchild;
} BiTNode, *BiTree, *SElemType;

//创建二叉树
Status CreateBiTree(BiTree &T)
{
    char ch;
    scanf("%c", &ch);

    if('#' == ch) T = NULL;
    else{
        if(!(T = (BiTNode *)malloc(sizeof(BiTNode)))) exit(OVERFLOW);
        T->data = ch;             //Create the root node
        CreateBiTree(T->lchild);  //Create left subtree
        CreateBiTree(T->rchild);  //Create right subtree
    }
    return OK;
}

//中序遍历二叉树
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



//后序遍历二叉树
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

//计算深度
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


int main()
{
    BiTree T; char p;
    CreateBiTree(T);
    
    InOrderTraverse(T);
    printf("\n");
    AfterOrderTraverse(T);
    printf("\n");

    printf("%d\n", DeepTree(T)); 
    
    return 0;
}
