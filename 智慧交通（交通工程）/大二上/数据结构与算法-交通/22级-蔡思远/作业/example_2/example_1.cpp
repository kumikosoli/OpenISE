#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct BiTNode {
    char data;
    struct BiTNode *lchild, *rchild;
} BiTNode, *BiTree;

void CreateBiTree(BiTree *T)
{
    char ch;
    scanf(" %c", &ch);

    if (ch == '#') {
        *T = NULL;
    } else {
        *T = (BiTNode *)malloc(sizeof(BiTNode));
        (*T)->data = ch;
        CreateBiTree(&((*T)->lchild));
        CreateBiTree(&((*T)->rchild));
    }
}

bool FindNode(BiTree T, char target, char path[], int top)
{
    if (T == NULL) {
        return false;
    }
    if (T->data == target) {
        path[top] = T->data;
        return true;
    }

    if (FindNode(T->lchild, target, path, top + 1) ||
        FindNode(T->rchild, target, path, top + 1)) {
        path[top] = T->data;
        return true;
    }

    return false;
}

bool FindPath(BiTree T, char target)
{
    char path[100]; // 存储路径的数组
    int top = 0;    // 栈顶指针

    if (FindNode(T, target, path, top)) {
        // 打印路径
        for (int i = top; i >= 0; i--) {
            printf("%c", path[i]);
        }
        return true;
    } else {
        return false;
    }
}

int main()
{
    BiTree T;
    CreateBiTree(&T);

    getchar(); // 吸收回车
    char target;
    scanf("%c", &target);

    if (!FindPath(T, target)) {
        printf("Not found");
    }

    return 0;
}
