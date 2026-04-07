#include <iostream>
#include <stack>
#include <string>
using namespace std;

bool matchparentheses(const string& sentence) {
    stack<char> parentheses;
    
    for (char parenthese : sentence) {
        if (parenthese == '(' || parenthese == '[') {
            parentheses.push(parenthese);
        } else if (parenthese == ')' || parenthese == ']') {
            if (parentheses.empty()) {
                return false;
            }
            char top = parentheses.top();
            parentheses.pop();
            if ((parenthese == ')' && top != '(') || (parenthese == ']' && top != '[')) {
                return false;
            }
        }
    }
    
    return parentheses.empty();
}

int main() {
    string sentence;
    cout << "请输入一段包含括号的字符：";
    
    while (getline(cin, sentence)) {
        if (sentence.empty()) {
            break;
        }
        
        if (matchparentheses(sentence)) {
            cout << "1" << endl;
        } else {
            cout << "0" << endl;
        }
    }
    
    return 0;
}