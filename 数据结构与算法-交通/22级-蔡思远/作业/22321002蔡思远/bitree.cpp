#include<stdio.h>
#include<stdlib.h>

typedef struct BiTNode{
    char data;
    struct BiTNode *lchild, *rchild;
}BiTNode, *BiTree;

char path[100]; //保存路径的字符数组
int top = -1; //栈顶指针

void CreateBiTree(BiTree *T) {
    char ch;
    scanf("%c", &ch);
    if(ch == '#') 
        *T = NULL;
    else {
        *T = (BiTNode*)malloc(sizeof(BiTNode));
        (*T)->data = ch;
        CreateBiTree(&(*T)->lchild);
        CreateBiTree(&(*T)->rchild);
    }
}

int GetPath(BiTree T, char x) {
    if(!T) return 0;   //如果节点为空，返回0
    path[++top] = T->data;   //如果节点不为空，将当前节点数据加入路径，开始进行判定
    if(T->data == x) return 1;   //如果是目标节点，返回1
    if(GetPath(T->lchild, x) || GetPath(T->rchild, x)) return 1;   //如果左子树或右子树找到了，返回1
    top--;   //否则，弹出路径栈顶，并返回0
    return 0;
}

void PrintPath() {   //由于路径是按照从根节点到目标节点的顺序压入栈的，直接按照从栈底到栈顶的顺序打印即可。
    for (int i = 0; i <= top; i++) {
        printf("%c", path[i]);
    }
}

int main() {
    BiTree T;
    CreateBiTree(&T);
    getchar();
    char x;
    scanf("%c", &x);
    GetPath(T,x);
    PrintPath();
    return 0;
}