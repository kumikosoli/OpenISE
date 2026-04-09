#include <stdio.h>
#include <stdlib.h>

typedef int Status;
typedef char TElemType;

#define OK           1
#define FALSE        0
#define OVERFLOW    -2

typedef struct BiTNode {
    TElemType data;
    struct BiTNode *lchild, *rchild;//指向左子树和右子树的指针 
} BiTNode, *BiTree, *SElemType;

Status CreateBiTree(BiTree &T)
{
    char ch;
    scanf(" %c", &ch);

    if('#' == ch) T = NULL;
    else{
        if(!(T = (BiTNode *)malloc(sizeof(BiTNode)))) exit(OVERFLOW);//创建节点,用malloc函数产生节点的内存空间 
        T->data = ch;
        T->lchild = NULL;
        T->rchild = NULL;
        CreateBiTree(T->lchild);
        CreateBiTree(T->rchild);
    }
    return OK;
}

Status InOrderTraverse(BiTree T)//中序：左根右 
{
    if(T != NULL){
        InOrderTraverse(T->lchild);
        printf("%c ",T->data);
        InOrderTraverse(T->rchild);
    }
    return OK;
} 

Status AfterOrderTraverse(BiTree T)//后序：左右根 
{
    if(T != NULL){
        AfterOrderTraverse(T->lchild);
        AfterOrderTraverse(T->rchild);
        printf("%c ",T->data);
    }
    return OK; 
} 
//计算二叉树深度 
int DeepTree(BiTree T)
{
    if(T != NULL){
        int leftHeight = DeepTree(T->lchild);
        int rightHeight = DeepTree(T->rchild);
        int maxHeight = leftHeight > rightHeight ? leftHeight : rightHeight;//最大深度
        return maxHeight + 1; 
    }
    else{
        return 0;
    }
}
int depth = 0;
// 使用递归的方法实现路径搜索
   Status PathSearch(BiTree T, TElemType target, BiTree path[])
{
    if (T == NULL) {
        return FALSE;
    }
    if (T->data == target) {
        path[depth++] = T; // 将当前节点添加到路径中
        return OK;
    }
    if (PathSearch(T->lchild, target, path)) {
        path[depth++] = T; // 将当前节点添加到路径中
        return OK;
    }
    if (PathSearch(T->rchild, target, path)) {
        path[depth++] = T; // 将当前节点添加到路径中
        return OK;
    }
    return FALSE;
}

int main()
{
    BiTree T;
    CreateBiTree(T);
    
    InOrderTraverse(T);
    printf("\n");
    AfterOrderTraverse(T);
    printf("\n");
    printf("%d\n", DeepTree(T)); 
    // 输入目标节点
    TElemType target;
    printf("请输入目标节点：");
    scanf(" %c", &target);

    // 创建存储路径的数组
    BiTree path[100];

    // 调用路径搜索函数
    if (PathSearch(T, target, path)) {
        printf("路径为：");
        for (int i = depth-1; i >= 0; i--) {
            printf("%c ", path[i]->data);
        }
        printf("\n");
    } else {
        printf("未找到目标节点\n");
    }
    return 0;
}
