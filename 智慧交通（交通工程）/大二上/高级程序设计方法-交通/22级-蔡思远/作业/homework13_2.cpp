#include <iostream>
#include <vector>
using namespace std;

// 思考题：
// 可以是自定义的类型，但需要满足一些条件：重载比较操作符；需要一个默认构造函数；重载<<操作符。

template <typename T>
class MyArray {
private:
    vector<T> data;

    // 冒泡排序
    void bubbleSort() {
        bool swapped;
        for (size_t i = 0; i < data.size() - 1; i++) {
            swapped = false;
            for (size_t j = 0; j < data.size() - i - 1; j++) {
                if (data[j] > data[j + 1]) {
                    swap(data[j], data[j + 1]);
                    swapped = true;
                }
            }
            if (!swapped) break;
        }
    }

public:
    MyArray(const vector<T>& init) : data(init) {}

    // 排序
    void sort() {
        bubbleSort();
    }

    // 反转
    void reverse() {
        size_t n = data.size();
        for (size_t i = 0; i < n / 2; i++) {
            swap(data[i], data[n - i - 1]);
        }
    }

    // 查找指定元素
    int find(const T& value) {
        for (size_t i = 0; i < data.size(); i++) {
            if (data[i] == value) {
                return i;
            }
        }
        return -1;
    }

    // 数组求和
    T sum() {
        T sum = 0;
        for (const T& elem : data) {
            sum += elem;
        }
        return sum;
    }

    void print() {
        for (const T& elem : data) {
            cout << elem << " ";
        }
        cout << endl;
    }
};

int main() {
    // int型
    vector<int> intVec;
    intVec.push_back(10);
    intVec.push_back(7);
    intVec.push_back(5);
    intVec.push_back(1);
    intVec.push_back(88);
    MyArray<int> intArray(intVec);
    intArray.sort();
    intArray.print();
    intArray.reverse();
    intArray.print();
    cout << "求和：" << intArray.sum() << endl;
    cout << "找到5的位置：" << intArray.find(5) << endl;

    // double型
    vector<double> doubleVec;
    doubleVec.push_back(1.1);
    doubleVec.push_back(3.3);
    doubleVec.push_back(2.5);
    doubleVec.push_back(5.7);
    doubleVec.push_back(4.9);
    MyArray<double> doubleArray(doubleVec);
    doubleArray.sort();
    doubleArray.print();
    doubleArray.reverse();
    doubleArray.print();
    cout << "求和：" << doubleArray.sum() << endl;
    cout << "找到3.3的位置：" << doubleArray.find(3.3) << endl;

    return 0;
}


