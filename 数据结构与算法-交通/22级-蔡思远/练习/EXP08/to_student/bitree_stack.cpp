#include <stdio.h>
#include <stdlib.h>

typedef int Status;
typedef char TElemType;

#define OK           1
#define ERROR        0
#define OVERFLOW    -2
#define STACK_INIT_SIZE 100 // 栈存储空间初始分配量
#define STACKINCREMENT 10 // 栈存储空间分配增量

// 二叉树存储结构 
typedef struct BiTNode {
    TElemType data;
    struct BiTNode *lchild, *rchild;
} BiTNode, *BiTree, *SElemType;

// 栈存储结构 
typedef struct{
    SElemType *base;
    SElemType *top;
    int stacksize;
}SqStack;

// 初始化栈（创建一个空栈） 
Status InitStack(SqStack *S)
{
    S->base = (SElemType *)malloc(STACK_INIT_SIZE * sizeof(SElemType));
    if(!S->base) exit(OVERFLOW); // 存储分配失败
    S->top = S->base; // 栈顶与栈底相同
    S->stacksize = STACK_INIT_SIZE; // 栈的最大长度等于初始长度
    return OK;
}

// 入栈 
Status Push(SqStack *S, BiTree e)
{
    if(S->top - S->base >= S->stacksize) // 栈满，追加存储空间
    {
        S->base = (SElemType *)realloc(S->base, (S->stacksize + STACKINCREMENT) * sizeof(SElemType));
        if(!S->base) exit(OVERFLOW); // 存储分配失败
        S->top = S->base + S->stacksize; // 栈顶指针为栈底指针加上栈之前的最大长度
        S->stacksize += STACKINCREMENT; // 栈当前的最大长度等于栈之前的最大长度与增加的长度之和
    }
    *(S->top++) = e; // 先赋值（栈中存放的为根结点的地址），后栈顶指针上移，等价于 *(S->top)=e; S->top=S->top+1; 
    return OK;
}

// 出栈 
Status Pop(SqStack *S, BiTree *e)
{
    if(S->top == S->base) return ERROR; // 栈空，返回ERROR
    *e = *(--S->top); // 栈顶指针先下移，后赋值（*e为根结点指针存放的地址值，赋值即改变根结点指针的指向），等价于 S->top=S->top-1; *e = *(S->top);  
	return OK;
}

// 判断空栈 
Status StackEmpty(SqStack *S)
{
    if (S->top == S->base)
	{
		return OK;
	}
	return ERROR;
}

// 递归创建二叉树 
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

// 输出结点值，实现Visit功能，后续通过函数指针 Status (*Visit)(TElemType e) 调用 
Status PrintElement(TElemType e)
{
    printf("%c", e);
    return OK;
}

// 非递归先序遍历 
Status PreOrderTraverse(BiTree T, Status (*Visit)(TElemType e))
{
	// 请完成该部分代码 // 
} 

// 非递归中序遍历 
Status InOrderTraverse(BiTree T, Status (*Visit)(TElemType e))
{
	// 请完成该部分代码 // 
}

// 非递归后序遍历 
Status AfterOrderTraverse(BiTree T, Status (*Visit)(TElemType e))
{
    SqStack q,*S;
    S = &q;
    InitStack(S);
    TElemType i=-1; // 指针数组r下标，初始化为-1
    BiTree p, r[STACK_INIT_SIZE]; // 辅助指针数组r，用于记录右孩子不为空的结点
    p = T;
    while(p || !StackEmpty(S))
    {
        if(p)
        {
            Push(S,p); // 根结点入栈
            p = p->lchild; // 遍历左子树
        }
        else
        {
            Pop(S,&p); // 根结点出栈
            if(!p->rchild)
            {
                if(!Visit(p->data))     return ERROR;          // 若右孩子为空，访问根结点
                p = NULL;                                       // 指针p格式化为空，满足下一次循环的出栈条件
            }
            else if(p == r[i])                                 // 判断出栈根结点是否为第二次出栈的右孩子非空的根结点
            {
                if(!Visit(p->data))     return ERROR;          // 若是，访问根结点
                i--;                                            // 指针数组下标减1
                p = NULL;                                       // 指针p格式化为空，满足下一次循环的出栈条件
            }
            else
            {
                r[++i] = p;                                     // 若右孩子不为空，指针数组r下标加1，记录根结点
                Push(S,p);                                      // 根结点再次入栈
                p = p->rchild;                                  // 遍历右子树
            }
        }
    }
	return OK;
} 

int main()
{
    BiTree T;
    CreateBiTree(T);
    
    PreOrderTraverse(T, PrintElement);
    printf("\n");
    InOrderTraverse(T, PrintElement);
    printf("\n");
//    AfterOrderTraverse(T, PrintElement);
    
    return 0;
}
