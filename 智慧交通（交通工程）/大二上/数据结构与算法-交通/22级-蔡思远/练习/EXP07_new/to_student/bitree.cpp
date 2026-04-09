#include <stdio.h>
#include <stdlib.h>

typedef int Status;
typedef int TElemType;

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
        
		//please finish the following parts
    }
    return OK;
}

Status InOrderTraverse(BiTree T)
{
	//please finish the following parts
	return OK
} 

Status AfterOrderTraverse(BiTree T)
{
	//please finish the following parts
	return OK 
} 

int DeepTree(BiTree T)
{
    //please finish the following parts
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
