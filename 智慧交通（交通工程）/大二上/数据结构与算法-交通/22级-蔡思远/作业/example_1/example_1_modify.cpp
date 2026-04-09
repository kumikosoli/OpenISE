#include <stdio.h>
#include <string.h>
int top=0;//栈顶
void push(char a[],char x)
{
    a[top++]=x;
}//进栈操作
void pop(char a[])
{
    a[--top]=0;
}//出栈操作
int main()
{
    char a[100],house[100];//定义两个数组，一个作为栈，一个存取输入的字符串用于遍历
    int i,j;
    printf("enter a string:\n");
//  scanf("%s",&a);
//	gets(a);
//	scanf("%[^\n]", &a);getchar();
//	fgets(a, sizeof(a), stdin);j=strlen(a)-1;
    j=strlen(a);//获取字符串长以便遍历每一个字符
    for (i=0;i<j;i++)//对a遍历并判断是否进栈
    {
        if (a[i]=='('||a[i]=='[')//若字符为左括号，进栈
        {
        	
            push(house,a[i]);
            if(i==(j-1)){
            	printf("%d\n",0);
            	break;
			}
            continue;

        }
        if (a[i]==')'||a[i]==']')//若字符为右括号，进一步判断
        {
            if ((a[i]==')'&&house[top-1]=='(')||(a[i]==']'&&house[top-1]=='['))//若该右括号与栈顶括号匹配，出栈
            {
                pop(house);
                continue;
            }
            else//若不匹配，则括号不匹配，输出0，循环结束
            {
                printf("0");
                top=1;//防止第一个字符不匹配时，栈也为空，重复输出
                break;
            }
        }
        else continue;//不为括号，遍历下一个字符
    }
    if (top==0)//括号全部匹配，栈空，输出1
    printf("%d\n",1);
    return 0;
}
