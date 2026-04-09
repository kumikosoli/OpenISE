#include <iostream>
#include <vector>
#include <list>
using namespace std;

// 时间复杂度：
// 入队：平均情况下为 O(1)。当需要重新分配内存时，为 O(n)（最坏情况）。
// 出队：O(n)。因为移除第一个元素需要移动所有其他元素。
class VectorQueue {
private:
    vector<int> data;

public:
    void push(int value) {
        data.push_back(value);
    }

    void pop() {
        if (!data.empty()) {
            data.erase(data.begin());
            cout << "队头元素出队" << endl;
        }
    }

    int front() {
        if (!data.empty()) {
            return data.front();
        }
        return -1;
    }

    int back() {
        if (!data.empty()) {
            return data.back();
        }
        return -1;
    }

    bool empty() {
        return data.empty();
    }
};

// 时间复杂度：
// push (入队)：O(1)。只涉及在链表的尾部添加一个新节点，并更新尾部节点的指针。
// pop (出队)：O(1)。只涉及移除头部节点，并更新头部指针。
class ListQueue {
private:
    list<int> data;

public:
    void push(int value) {
        data.push_back(value);
    }

    void pop() {
        if (!data.empty()) {
            data.pop_front();
            cout << "队头元素出队" << endl;
        }
    }

    int front() {
        if (!data.empty()) {
            return data.front();
        }
        return -1;
    }

    int back() {
        if (!data.empty()) {
            return data.back();
        }
        return -1;
    }

    bool empty() {
        return data.empty();
    }
};

int main() {
    VectorQueue vQueue;
    ListQueue lQueue;

    // 入队
    cout << "VectorQueue:" << endl;
    vQueue.push(2);
    vQueue.push(3);
    vQueue.push(9);
    // 返回队头元素
    cout << "Front: " << vQueue.front() << endl;
    // 返回队尾元素
    cout << "Back: " << vQueue.back() << endl;
    //出队
    vQueue.pop();
    cout << "New Front: " << vQueue.front() << endl;
    // 判断队列是否为空
    cout << "Is empty? " << (vQueue.empty() ? "Yes" : "No") << endl;
    
    // 入队
    cout << "\nTesting ListQueue:" << endl;
    lQueue.push(4);
    lQueue.push(5);
    lQueue.push(7);
    // 返回队头元素
    cout << "Front: " << lQueue.front() << endl;
    // 返回队尾元素
    cout << "Back: " << lQueue.back() << endl;
    // 出队
    lQueue.pop();
    cout << "New Front: " << lQueue.front() << endl;
    lQueue.pop();
    lQueue.pop();
    // 判断队列是否为空
    cout << "Is empty? " << (lQueue.empty() ? "Yes" : "No") << endl;

    return 0;
}

