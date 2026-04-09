#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
        T->data = ch;
        CreateBiTree(T->lchild);
        CreateBiTree(T->rchild); 
        
    }
    return OK;
}

// 判断路径是否应该包含当前节点
bool pathIncludesNode(BiTree T, TElemType elem) {
    if (T == NULL) {   //当前节点为空，该路径肯定不包含目标节点
        return false;
    }
    
    if (T->data == elem) {   //当前节点就是目标节点，将该节点放入路径
        printf("%c", T->data);
        return true;
    }
    
    if (pathIncludesNode(T->lchild, elem) || pathIncludesNode(T->rchild, elem)) {   //如果左子树或右子树包含目标节点，那么当前节点就在路径上
        printf("%c", T->data);
        return true;
    }
    
    return false;   //左右子树都不包含目标节点，返回false
}

// 使用前序遍历方式打印从根节点到指定节点的路径
void get_path(BiTree T, TElemType elem) {
    if (pathIncludesNode(T, elem)) {
        printf("");
    } else {
        printf("未找到路径");
    }
}

int main() {
    BiTree T;
    CreateBiTree(T);
    getchar();
    char x;
    scanf("%c", &x);
    get_path(T, x);
    return 0;
}