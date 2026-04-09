#include <iostream>
using namespace std;

class Matrix {
private:
    int m;
    int n;
    int** data; 

public:
    Matrix(int* arr, int m, int n):m(m),n(n) {    //设计有参构造函数

        data = new int*[m];   //分配内存空间
        for (int i = 0; i < m; ++i) {
            data[i] = new int[n];
        }
        
        int k = 0;
        for (int i = 0; i < m; ++i) {    //用一维数组初始化数据成员二维数组
            for (int j = 0; j < n; ++j) {
                data[i][j] = arr[k++];
            }
        }
    }
    
    ~Matrix() {   //析构函数
        delete[] data;
    }
    
    void printMatrix() {
        int top = 0, bottom = m - 1, left = 0, right = n - 1;
        
        for (int i = 0; i < m; ++i) {   //输出该二维数组
            for (int j = 0; j < n; ++j) {
                cout << data[i][j] << " ";
            }
            cout << endl;
        }
        for (int i = left; i <= right; ++i) {   //从左到右输出上边
            cout << data[top][i] << " ";
        }
        ++top;

        for (int i = top; i <= bottom; ++i) {   //从上到下输出右边
            cout << data[i][right] << " ";
        }
        --right;
            

        for (int i = right; i >= left; --i) {   //从右到左输出下边
            cout << data[bottom][i] << " ";
        }
        --bottom;

        for (int i = bottom; i >= top; --i) {   //从下到上输出左边
            cout << data[i][left] << " ";
        }
        ++left;
    }
};

int main() {
    int arr[] = {1, 2, 5, 9, 11, 12, 13, 17, 19, 20, 21, 23, 25, 28, 29, 30};
    int m = 4;
    int n = 4;
    
    Matrix matrix(arr, m, n);
    matrix.printMatrix();
    
    return 0;
}