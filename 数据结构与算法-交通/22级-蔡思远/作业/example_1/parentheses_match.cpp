#include<stdio.h>

int main() {
    char s, Q[1000];  
    int top = 0;
    while (1) {
    	s = getchar();
    	if (s == '\n') break;
    	else if (s != '(' && s != ')' && s != '[' && s != ']') continue;
		if (top > 0 && ((Q[top-1] == '(' && s == ')') || (Q[top-1] == '[' && s == ']'))){
				top--; 
        }
		else {Q[top++] = s;
		}
    }
    if (top) printf("0");
    else printf("1");
	return 0;
}

