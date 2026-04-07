#include <stdio.h>
#include <stdbool.h>
#define MAX_SIZE 100

// ’ªΩ·ππ∂®“Â
typedef struct 
{
    char data[MAX_SIZE];
    int top;
} stack;

// ≥ı ºªØ’ª
void init_stack(stack *s) 
{
    s->top = -1;
}

// ≈–∂œ’ª «∑ÒŒ™ø’
bool isEmpty(stack *s) 
{
    return s->top == -1;
}

// ≈–∂œ’ª «∑Ò“—¬˙
bool isFull(stack *s) 
{
    return s->top == MAX_SIZE - 1;
}

// »Î’ª
void push(stack *s, char c) 
{
    if (isFull(s)) 
	{
        printf("Stack is full.\n");
        return;
    }
    s->data[++s->top] = c;
}

// ≥ˆ’ª
char pop(stack *s) 
{
    if (isEmpty(s)) 
	{
        printf("stack «ø’°£\n");
        return '\0';
    }
    return s->data[s->top--];
}

// ºÏ—È¿®∫≈ «∑Ò∆•≈‰
bool isMatching(char exp[]) 
{
    stack s;
    init_stack(&s);
    
    for (int i = 0; exp[i] != '\0'; i++) 
	{
        if (exp[i] == '(' || exp[i] == '[') 
		{
            push(&s, exp[i]);
        } else if (exp[i] == ')' || exp[i] == ']') 
		{
            if (isEmpty(&s)) 
			{
                return false;
            }
            
            char top = pop(&s);
            if ((exp[i] == ')' && top != '(') || (exp[i] == ']' && top != '[')) {
                return false;
            }
        }
    }
    
    return isEmpty(&s);
}

int main() 
{
    char exp[MAX_SIZE];
    
    printf("Enter an expression: ");
    fgets(exp, sizeof(exp), stdin);
    
    if (isMatching(exp)) 
	{
        printf("¿®∫≈ «∆•≈‰µƒ\n");
    } else 
	{
        printf("¿®∫≈≤ª∆•≈‰\n");
    }
    
    return 0;
}
