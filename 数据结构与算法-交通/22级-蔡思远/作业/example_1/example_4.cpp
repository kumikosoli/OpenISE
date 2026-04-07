#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LENGTH 1000

int matching(char left, char right) {
    if (left == '(' && right == ')') {
        return 1; 
    } else if (left == '[' && right == ']') {
        return 1;
    } else {
        return 0;
    }
}

int check_parentheses(char* expression) {
    int len = strlen(expression);
    char stack[LENGTH];
    int top = -1;//³õÊ¼Öµ-1´ú±íÕ»¿Õ 
    for (int i = 0; i < len; i++) {
        char ch = expression[i];
        if (ch == '(' || ch == '[') {
            stack[++top] = ch;//ÈôÎª×óÀ¨ºÅ£¬Ñ¹ÈëÕ»ÖÐ 
        } else if (ch == ')' || ch == ']') {//ÈôÎªÓÒÀ¨ºÅ£¬ÅÐ¶ÏÊÇ·ñÎª¿ÕÕ» 
            if (top < 0 || !matching(stack[top], ch)) {
                return 0;
            }
            top--;//½«Õ»¶¥ÔªËØ³öÕ» 
        }
    }
    return top < 0;
}

int main() {
    char expression[LENGTH];
    printf("ÊäÈëÀ¨ºÅ´®£º\n");
    fgets(expression, LENGTH, stdin);
    int result = check_parentheses(expression);
    if (result) {
        printf("À¨ºÅÆ¥Åä\n");
    } else {
        printf("À¨ºÅ²»Æ¥Åä\n");
    }
    return 0;
}

