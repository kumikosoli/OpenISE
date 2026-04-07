#include<stdio.h>
#include<malloc.h>
#include<string.h>
#include<stdlib.h>
#define STACK_INT_SIZE 100 
#define STACKINCRENMENT 2
typedef struct {//构建栈结构 
	int *base;
	int *top;
	int stacksize;
}Sqstack;//栈类型名 
void InitStack(Sqstack &S);//创造一个空栈 
void Push(Sqstack &S,char &e);//元素e入栈 
void Pop(Sqstack &S,char &c);//以e返回栈顶值 
int main(){
	char e,a[100],c;
	Sqstack S;//创建栈 
	InitStack(S);//构造空栈 
	gets(a);//输入字符串 
	int l=strlen(a);//得到字符串的长度 
	for(int i=0;i<l;i++){
		e=a[i];
		if(e=='('||e=='['){//判断为左括号入栈 
		Push(S,e);
		}	
		if(a[0]==')'||a[0]==']'){//第一 个元素为右括号结束 
				break;
			}
		if(e==')'){//匹配成功时出栈 
				Pop(S,c);
					if(c!='('){
					Push(S,c);
				}
			}
		if(e==']'){//匹配成功时出栈 
				Pop(S,c);
				if(c!='['){
					Push(S,c);
				}
			}
	}
	if(S.top==S.base){//最后栈空则匹配成功 
		 printf("1");
			}
			else{//反之不成功 
				 printf("0");
			}      
}
void InitStack(Sqstack &S){//定义空栈 
	S.base=(int *)malloc(STACK_INT_SIZE *sizeof(int));
	if(!S.base)exit(-1);
	S.top=S.base;
	S.stacksize=STACK_INT_SIZE;
}
void Push(Sqstack &S,char &e){//定义入栈函数 
	*S.top++=e;
}
void Pop(Sqstack &S,char &c){//定义出栈函数 
	    c=*--S.top;
}

