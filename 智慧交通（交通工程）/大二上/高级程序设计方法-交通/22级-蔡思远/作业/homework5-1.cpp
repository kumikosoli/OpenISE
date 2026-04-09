#include<iostream>
using namespace std;

class Array {
    private:
        int size;
        int *p;   //数组的首指针

    public:
        Array() {   //默认构造函数
            size = 0;
            p = nullptr;
        }

        Array(int n) {    //有参构造函数
            size = n;
            p = new int[size];
            for(int i = 0; i < size; i++) {
                p[i] = 0;
            }
        }

        Array(const Array &arr) {    //拷贝构造函数
            size = arr.size;
            p = new int[size];
            for(int i = 0; i < size; i++) {
                p[i] = arr.p[i];
            }
        }

        ~Array() {    //析构函数
            delete[] p;
        }

        void add(int value) {    //加法
            for(int i = 0; i < size; i++) {
                p[i] += value;
            }
        }

        void sub(int value) {     //减法
            for(int i = 0; i < size; i++) {
                p[i] -= value;
            }
        }

        void mul(int value) {     //乘法
            for(int i = 0; i < size; i++) {
                p[i] *= value;
            }
        }

        void print() { 
            for(int i = 0; i < size; i++) {
                cout << p[i] << " ";
            }
            cout << endl;
        }
};

int main() {
    Array arr(5); 
    cout << "向量大小为5，每个元素初始值为0" << endl;
    cout << "每个元素加4的结果为：" ;
    arr.add(4); 
    arr.print();
    cout << "每个元素再减2的结果为：" ;
    arr.sub(2); 
    arr.print();
    cout << "每个元素再乘5的结果为：" ;
    arr.mul(5);
    arr.print();
    return 0;
}