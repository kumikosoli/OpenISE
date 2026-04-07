#include <stdio.h>
#include <stdlib.h>


//十字链表结点
typedef  struct node
{
	int row, col, val; //矩阵三元组：行头，列头，值
    struct node *down, *right; //指针域：下指针，右指针
}Node, *LNode;


//十字链表结构体
typedef struct crossLink {
    LNode *rHead, *cHead; //行头指针
    int rN, cN, tN; //行数，列数，非零元素个数
}CrossLink;


// ��������ʮ������ 
void insert_linkedmat(CrossLink m, Node *pInsert)
{
    Node *p;
    int i, j;
    if(!pInsert)
    {
        return;
    }
    i = pInsert->row;
    j = pInsert->col;

    if(m.rHead[i] == NULL || m.rHead[i]->col > j)    //ͷ����
    {
        pInsert->right = m.rHead[i];
        m.rHead[i] = pInsert;
    }
    else
    {
        //Ѱ�����б��еĲ���λ��
        p = m.rHead[i];
        while(p)
        {
            if(p->right && p->right->col < j)
            {
                p = p->right;
            }
            else if(p->right && p->right->col > j )   //�м����
            {
                if(p->col < j)
                {
                    pInsert->right = p->right;
                    p->right = pInsert;                        
                    p = NULL;
                }
            }
            else if(!p->right && p->col < j)         //������
            {
                pInsert->right = p->right;
                p->right = pInsert;
                p = NULL;
            }
        }
    }//����в���


    if(m.cHead[j] == NULL || m.cHead[j]->row > i)    //ͷ����
    {
        pInsert->down = m.cHead[j];
        m.cHead[j] = pInsert;
    }
    else
    {
        //Ѱ�����б��еĲ���λ��
        p = m.cHead[j];
        while(p)
        {
            if(p->down && p->down->row < i)
            {
                p = p->down;
            }
            else if(p->down && p->down->row > i)    //�м����
            {
                if(p->row < i)
                {
                    pInsert->down = p->down;
                    p->down = pInsert;                        
                    p = NULL;
                }
            }
            else if(!p->down && p->row < i)         //������
            {
                pInsert->down = p->down;
                p->down = pInsert;
                p = NULL;

            }
        }           
    }//����в���
}


// ����ʮ������ 
CrossLink crt_linkedmat(CrossLink m)
{  
	int i,r,c,v;
	Node *p;
	
    scanf("%d %d %d", &m.rN, &m.cN, &m.tN);// ����������������Ԫ�ظ���
    
   	// ��ʼ�� 
	m.rHead = (LNode*)malloc((m.rN+1)*sizeof(LNode));
	m.cHead = (LNode*)malloc((m.cN+1)*sizeof(LNode));
    for (i=1; i<=m.rN; i++) m.rHead[i] = NULL;
    for (i=1; i<=m.cN; i++) m.cHead[i] = NULL;
    
	for(i=1; i<=m.tN; i++)
	{
		scanf("%d %d %d",&r,&c,&v); // ������Ԫ�飺�кţ��кţ�ֵ 
	
		// ��ʱ��� 
		p = (Node *)malloc(sizeof(Node));	
        p->row = r;
        p->col = c;
        p->val = v;
        p->right = NULL;
        p->down = NULL;
        
		insert_linkedmat(m, p); 
    }
	
	return m;
}


//十字链表相加
CrossLink add_linkedmat(CrossLink m1, CrossLink m2){

    int i,j;   //用于遍历行、列

    Node *pa = NULL, *pb = NULL; //矩阵m1和矩阵m2行链表中的某结点指针
	Node *pre = NULL; //pre为矩阵1当前节点pa的前驱
	                                            
    LNode *hl; //矩阵m1的每一列的链表头
    hl = (LNode *)malloc((m1.cN + 1) *sizeof(LNode));
	
	// pa,pb指向矩阵当前行第一个非零结点
    pa = m1.rHead[1];
    pb = m2.rHead[1];
    i = 1; //初始化行号

	//hl初始化指向每一列第一个非零结点
    for(j =1; j <= m1.cN; ++j)
    {
        hl[j] = m1.cHead[j];
    }

    Node *pTmp = NULL; //临时结点
    while(i <= m1.rN)
    {         
        while(pb)
        {    
            pTmp = (Node *)malloc((m1.rN + 1) *sizeof(Node));
            pTmp->row = pb->row;
            pTmp->col = pb->col;
            pTmp->val = pb->val;
			
			//矩阵m1当前行没有非零结点或矩阵m2当前行第一个非零结点在矩阵m1之前
            if(pa == NULL || pa->col > pb->col)
            {                     
                pre = pTmp;
                //插入临时结点
                insert_linkedmat(m1, pTmp);
                hl[pTmp->col] = pTmp;
                ++m1.tN;
            }
            //矩阵m2当前行第一个非零结点在矩阵m1之后
            else if(pa != NULL && pa->col < pb->col)
            {
                pre = pa;
                if(pa->right)
                {
                    pa = pa->right;
                    continue;
                }
                else
                {
                    insert_linkedmat(m1, pTmp);
                    hl[pTmp->col] = pTmp;
                }
            }
            //矩阵m1和m2当前行当前列均有非零元素
            else if(pa->col == pb->col)
            {
                pa->val += pb->val;
				
				//相加后为零，删除结点
                if(pa->val == 0)
                {
                    if(pre == NULL)
                    {
                        m1.rHead[pa->row] = pa->right;
                    }
                    else
                    {
                        pre->right = pa->right;
                    }
                    pTmp = pa;
                    pa = pa->right;

                    if(m1.cHead[pTmp->col] == pTmp)
                    {
                        m1.cHead[pTmp->col] = hl[pTmp->col] = pTmp->down;
                    }
                    else
                    {
                        hl[pTmp->col]->down = pTmp->down;
                    }
                    free(pTmp);
                    --m1.tN;
                }
            }
            pb = pb->right;
        }
        
        pre = NULL;
        i++;
        pa = m1.rHead[i];
        pb = m2.rHead[i];
    }
	return m1; 
}


// ���������
void display_col(CrossLink m){
    for (int i=1; i<=m.cN; i++)
    {
        if (NULL != m.cHead[i])
        {
           LNode p = m.cHead[i];
            while (NULL != p)
            {
                printf("%d %d %d\n", p->row, p->col, p->val);
                p = p->down;
            }
        }
    }
}


// ��������� 
void display_row(CrossLink m){
    for (int i=1; i<=m.rN; i++)
    {
        if (NULL != m.rHead[i])
        {
           LNode p = m.rHead[i];
            while (NULL != p)
            {
                printf("%d %d %d\n", p->row, p->col, p->val);
                p = p->right;
            }
        }
    }
}


int main(){
	
	CrossLink ma, mb, mc;
	ma = crt_linkedmat(ma);
//	display_row(ma);
//	display_col(ma);
	
	mb = crt_linkedmat(mb);
//	display_row(mb);
//	display_col(mb);

	mc = add_linkedmat(ma, mb);
    display_row(mc);
    display_col(mc);
	
}
