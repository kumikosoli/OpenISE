#include <iostream>
#include <stack>
using namespace std;


class StackQueue {
private:
    stack<int> stack1;
    stack<int> stack2;

public:
    void push(int x) {
        stack1.push(x);
    }

    void pop() {
        if (stack2.empty()) {
            while (!stack1.empty()) {
                stack2.push(stack1.top());
                stack1.pop();
            }
        }
        if (!stack2.empty()) {
            stack2.pop();
            cout << "队头元素出队" << endl;
        }
    }

    int front() {
        if (stack2.empty()) {
            while (!stack1.empty()) {
                stack2.push(stack1.top());
                stack1.pop();
            }
        }
        return stack2.empty() ? -1 : stack2.top();
    }

    bool empty() {
        return stack1.empty() && stack2.empty();
    }
};

int main() {
    StackQueue queue;
    // 入队
    queue.push(1);
    queue.push(2);
    queue.push(3);
    queue.push(4);
    // 返回队头元素
    cout << "Front: " << queue.front() << endl; 
    // 出队
    queue.pop();
    cout << "New Front: " << queue.front() << endl;
    // 判断队列是否为空
    cout << "Is empty? " << (queue.empty() ? "Yes" : "No") << endl; 
    queue.pop();
    queue.pop();
    queue.pop();
    cout << "Is empty? " << (queue.empty() ? "Yes" : "No") << endl; 

    return 0;
}


