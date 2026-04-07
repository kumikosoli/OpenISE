#include <stdio.h>
#include <stdlib.h>


// 十字链表结点 
typedef  struct node
{
	int row, col, val; // 矩阵三元组：行号，列号，值 
    struct node *down, *right; // 指针域：下指针，右指针 
}Node, *LNode;


// 十字链表结构体 
typedef struct crossLink {
    LNode *rHead, *cHead; // 行头指针，列头指针
    int rN, cN, tN; // 行数，列数，非零元素个数
}CrossLink;


// 将结点插入十字链表 
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

    if(m.rHead[i] == NULL || m.rHead[i]->col > j)    //头插入
    {
        pInsert->right = m.rHead[i];
        m.rHead[i] = pInsert;
    }
    else
    {
        //寻查在行表中的插入位置
        p = m.rHead[i];
        while(p)
        {
            if(p->right && p->right->col < j)
            {
                p = p->right;
            }
            else if(p->right && p->right->col > j )   //中间插入
            {
                if(p->col < j)
                {
                    pInsert->right = p->right;
                    p->right = pInsert;                        
                    p = NULL;
                }
            }
            else if(!p->right && p->col < j)         //最后插入
            {
                pInsert->right = p->right;
                p->right = pInsert;
                p = NULL;
            }
        }
    }//完成行插入


    if(m.cHead[j] == NULL || m.cHead[j]->row > i)    //头插入
    {
        pInsert->down = m.cHead[j];
        m.cHead[j] = pInsert;
    }
    else
    {
        //寻查在列表中的插入位置
        p = m.cHead[j];
        while(p)
        {
            if(p->down && p->down->row < i)
            {
                p = p->down;
            }
            else if(p->down && p->down->row > i)    //中间插入
            {
                if(p->row < i)
                {
                    pInsert->down = p->down;
                    p->down = pInsert;                        
                    p = NULL;
                }
            }
            else if(!p->down && p->row < i)         //最后插入
            {
                pInsert->down = p->down;
                p->down = pInsert;
                p = NULL;

            }
        }           
    }//完成列插入
}


// 创建十字链表 
CrossLink crt_linkedmat(CrossLink m)
{  
	int i,r,c,v;
	Node *p;
	
    scanf("%d %d %d", &m.rN, &m.cN, &m.tN);// 行数，列数，非零元素个数
    
   	// 初始化 
	m.rHead = (LNode*)malloc((m.rN+1)*sizeof(LNode));
	m.cHead = (LNode*)malloc((m.cN+1)*sizeof(LNode));
    for (i=1; i<=m.rN; i++) m.rHead[i] = NULL;
    for (i=1; i<=m.cN; i++) m.cHead[i] = NULL;
    
	for(i=1; i<=m.tN; i++)
	{
		scanf("%d %d %d",&r,&c,&v); // 矩阵三元组：行号，列号，值 
	
		// 临时结点 
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


// 十字链表相加 
CrossLink add_linkedmat(CrossLink m1, CrossLink m2){
	
    CrossLink temp; 
    Node *p;
    
    temp.rN=m1.rN, temp.cN=m1.cN, temp.tN=0;
	temp.rHead = (LNode*)malloc((m1.rN+1)*sizeof(LNode));
	temp.cHead = (LNode*)malloc((m1.cN+1)*sizeof(LNode));
	
	for (int i=1; i<=temp.rN; i++) temp.rHead[i] = NULL;
    for (int i=1; i<=temp.cN; i++) temp.cHead[i] = NULL;
    for (int i=1; i<=m1.rN; i++){
    	if (!(NULL == m1.rHead[i]&&NULL == m2.rHead[i]))
        {
           LNode p1 = m1.rHead[i];
           LNode p2 = m2.rHead[i];
            while (!(NULL == p1&&NULL == p2))
            {
            	// p1当前位置为空，直接插入 
            	if(NULL == p1){
            		p = (Node *)malloc(sizeof(Node));	
        			p->row = p2->row;
        			p->col = p2->col;
        			p->val = p2->val;
        			p->right = NULL;
        			p->down = NULL;
        			insert_linkedmat(temp, p);
            		p2=p2->right;
				}
				
				// p2当前位置为空，直接插入 
				else if(NULL == p2){
					p = (Node *)malloc(sizeof(Node));	
        			p->row = p1->row;
        			p->col = p1->col;
        			p->val = p1->val;
        			p->right = NULL;
        			p->down = NULL;
        			insert_linkedmat(temp, p);
					p1=p1->right;
				}
				
				// p1在p2前，插入后移动p1
                else if(p1->col < p2->col){
                	p = (Node *)malloc(sizeof(Node));	
        			p->row = p1->row;
        			p->col = p1->col;
        			p->val = p1->val;
        			p->right = NULL;
        			p->down = NULL;
        			insert_linkedmat(temp, p);
                	p1=p1->right;
				}
				
				// p1在p2后，插入后移动p2 
				else if(p1->col>p2->col){
					p = (Node *)malloc(sizeof(Node));	
        			p->row = p2->row;
        			p->col = p2->col;
        			p->val = p2->val;
        			p->right = NULL;
        			p->down = NULL;
        			insert_linkedmat(temp, p);
                	p2=p2->right;
				}
				
				// m1 m2 当前位置均非空 
				else if(p1->col == p2->col){
					int a;
					a=p1->val+p2->val;
					
					// 和不为0则插入 
					if(a!=0){
						p = (Node *)malloc(sizeof(Node));	
        				p->row = p1->row;
        				p->col = p1->col;
        				p->val = a;
        				p->right = NULL;
        				p->down = NULL;
        				insert_linkedmat(temp, p);
        				
					}
					
		 			// 和为0则跳过，避免了删除结点的操作 
					p2=p2->right;
					p1=p1->right;
				}
				
            }
        }
	}
	return temp;
}


// 按列序输出
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


// 按行序输出 
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
//display_row(mb);
//display_col(mb);
//printf("-------------------------------------\n");

	mc = add_linkedmat(ma, mb);
    display_row(mc);
//    printf("-------------------------------------\n");
    display_col(mc);
	
}
