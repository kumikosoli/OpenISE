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

char path[200] = ""; //栈，存储根结点到指定结点间的路径
int top = 0; //栈顶索引值

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

Status InOrderTraverse(BiTree &T)
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

Status FindPath(BiTree T, char p)
{
	if(T == NULL)
        return FALSE;
    if (T->data == p) {
        path[top++] = p;
        return OK;
    }
    if (FindPath(T->lchild, p) || FindPath(T->rchild, p)) {
        path[top++] = T->data;
        return OK;
    }
    return FALSE;
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
    
    getchar(); //吸收回车
	scanf("%c", &p);
	FindPath(T, p);
    while (top > 0) printf("%c", path[--top]); //打印路径
    
    return 0;
}
