#include <stdio.h>
#include <stdlib.h>

typedef int Status;
typedef char TElemType;

#define OK           1
#define ERROR        0
#define OVERFLOW    -2
#define STACK_INIT_SIZE 100 //栈存储空间初始分配量
#define STACKINCREMENT 10 //栈存储空间分配增量

//二叉树存储结构
typedef struct BiTNode {
    TElemType data;
    struct BiTNode *lchild, *rchild;
} BiTNode, *BiTree, *SElemType;

//栈存储结构
typedef struct{
    SElemType *base;
    SElemType *top;
    int stacksize;
}SqStack;

//初始化栈
Status InitStack(SqStack *S)
{
    S->base = (SElemType *)malloc(STACK_INIT_SIZE * sizeof(SElemType));
    if(!S->base) exit(OVERFLOW); // �洢����ʧ��
    S->top = S->base; // ջ����ջ����ͬ
    S->stacksize = STACK_INIT_SIZE; // ջ����󳤶ȵ��ڳ�ʼ����
    return OK;
}

// ��ջ 
Status Push(SqStack *S, BiTree e)
{
    if(S->top - S->base >= S->stacksize) // ջ����׷�Ӵ洢�ռ�
    {
        S->base = (SElemType *)realloc(S->base, (S->stacksize + STACKINCREMENT) * sizeof(SElemType));
        if(!S->base) exit(OVERFLOW); // �洢����ʧ��
        S->top = S->base + S->stacksize; // ջ��ָ��Ϊջ��ָ�����ջ֮ǰ����󳤶�
        S->stacksize += STACKINCREMENT; // ջ��ǰ����󳤶ȵ���ջ֮ǰ����󳤶������ӵĳ���֮��
    }
    *(S->top++) = e; // �ȸ�ֵ��ջ�д�ŵ�Ϊ�����ĵ�ַ������ջ��ָ�����ƣ��ȼ��� *(S->top)=e; S->top=S->top+1; 
    return OK;
}

// ��ջ 
Status Pop(SqStack *S, BiTree *e)
{
    if(S->top == S->base) return ERROR; // ջ�գ�����ERROR
    *e = *(--S->top); // ջ��ָ�������ƣ���ֵ��*eΪ�����ָ���ŵĵ�ֵַ����ֵ���ı�����ָ���ָ�򣩣��ȼ��� S->top=S->top-1; *e = *(S->top);  
	return OK;
}

// �жϿ�ջ 
Status StackEmpty(SqStack *S)
{
    if (S->top == S->base)
	{
		return OK;
	}
	return ERROR;
}

// �ݹ鴴�������� 
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

//输出结点值，实现Visit功能，后续通过函数指针 Status (*Visit)(TElemType e) 调用
Status PrintElement(TElemType e)
{
    printf("%c", e);
    return OK;
}


//Push:入栈；Pop:出栈；StackEmpty:判断空栈；Visit/PrintElement:访问（输出）结点值

//非递归先序遍历
Status PreOrderTraverse(BiTree T, Status (*Visit)(TElemType e)) //Status (*Visit)(TElemType e) = PrintElement，主函数中填写后者
{
    SqStack q, *S;
    S = &q;
    InitStack(S);
    BiTree p;
    Push(S, T); //根结点入栈
    while(!StackEmpty(S))
    {
        Pop(S, &p); //根结点出栈
        while(p)
        {
        	//访问根结点
            if(!Visit(p->data))	return ERROR;
            
            //如果右孩子不为空，则右孩子入栈
            if(p->rchild) 
            {
                Push(S,p->rchild);
            }
            
            //遍历左子树
            p = p->lchild;
        }
    }
    return OK;
} 

//非递归中序遍历
Status InOrderTraverse(BiTree T, Status (*Visit)(TElemType e))
{
    SqStack q,*S;
    S = &q;
    InitStack(S);
    BiTree p;
    p = T; //p指向根结点
    while(p || !StackEmpty(S))
    {
        if(p)
        {
            Push(S,p); //根结点入栈
            p = p->lchild; //遍历左子树
        }
        else
        {
            Pop(S,&p); //根结点出栈
            if(!Visit(p->data))	return ERROR; //访问根节点
            p = p->rchild; // 
        }
    }
    return OK;

}

// �ǵݹ������� 
Status AfterOrderTraverse(BiTree T, Status (*Visit)(TElemType e))
{
    SqStack q,*S;
    S = &q;
    InitStack(S);
    TElemType i=-1; // ָ������r�±꣬��ʼ��Ϊ-1
    BiTree p, r[STACK_INIT_SIZE]; // ����ָ������r�����ڼ�¼�Һ��Ӳ�Ϊ�յĽ��
    p = T;
    while(p || !StackEmpty(S))
    {
        if(p)
        {
            Push(S,p); // �������ջ
            p = p->lchild; // ����������
        }
        else
        {
            Pop(S,&p); // ������ջ
            if(!p->rchild)
            {
                if(!Visit(p->data))     return ERROR;          // ���Һ���Ϊ�գ����ʸ����
                p = NULL;                                       // ָ��p��ʽ��Ϊ�գ�������һ��ѭ���ĳ�ջ����
            }
            else if(p == r[i])                                 // �жϳ�ջ������Ƿ�Ϊ�ڶ��γ�ջ���Һ��ӷǿյĸ����
            {
                if(!Visit(p->data))     return ERROR;          // ���ǣ����ʸ����
                i--;                                            // ָ�������±��1
                p = NULL;                                       // ָ��p��ʽ��Ϊ�գ�������һ��ѭ���ĳ�ջ����
            }
            else
            {
                r[++i] = p;                                     // ���Һ��Ӳ�Ϊ�գ�ָ������r�±��1����¼�����
                Push(S,p);                                      // ������ٴ���ջ
                p = p->rchild;                                  // ����������
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
