#include <iostream>
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

        void add(int value) {    //对数组所有元素加上一个值
            for(int i = 0; i < size; i++) {
                p[i] += value;
            }
        }

        int getSize() {        //获取数组大小
            return this->size;
        }

        
        int getElement(int index) {    //获取数组指定位置的元素
            return p[index];
        }

        void print() {
            for(int i = 0; i < size; i++) {
                cout << p[i] << " ";
            }
            cout << endl;
        }
};

typedef void(*Operation)(Array* arr1, Array* arr2);

void vectoradd(Array* arr1, Array* arr2) {  //两个向量相加
    int size = arr1->getSize();
    Array result(size);
    for (int i = 0; i < size; i++) {
        result.add(arr1->getElement(i) + arr2->getElement(i));
    }
    cout << "两个向量相加的结果为：";
    result.print();
}

void dotproduct(Array* arr1, Array* arr2) {    //两个向量点积
    int dotProduct = 0;
    for (int i = 0; i < arr1->getSize(); i++) {
        dotProduct += arr1->getElement(i) * arr2->getElement(i);
    }
    cout << "两个向量的点积为：" << dotProduct << endl;
}

void op3(Array* arr1, Array* arr2) {   //(2*arr1 + arr2)的结果
    int size = arr1->getSize();
    Array result(size);
    for (int i = 0; i < size; i++) {
        result.add(2 * arr1->getElement(i) + arr2->getElement(i));
    }
    cout << "(2*arr1 + arr2) 的结果为：";
    result.print();
}

void PublicFunc(Array* arr1, Array* arr2, Operation op) {
    op(arr1, arr2);
}

int main() {
    Array* arr1 = new Array(5); 
    Array* arr2 = new Array(5); 
    for(int i=0;i<5;i++) {
        arr1->add(i+1);    //arr1的元素分别为1到5
        arr2->add(i+6);    //arr2的元素分别为6到10
    };
    cout << "arr1的元素分别为1到5,arr2的元素分别为6到10" << endl;
    PublicFunc(arr1, arr2, vectoradd);
    PublicFunc(arr1, arr2, dotproduct);
    PublicFunc(arr1, arr2, op3);
    delete arr1;
    delete arr2;
    return 0;
}