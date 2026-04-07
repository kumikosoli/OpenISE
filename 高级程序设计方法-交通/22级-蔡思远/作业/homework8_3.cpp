#include<iostream>
#include<string>
#include<vector>
using namespace std;

class Matrix{
private:
    int nRows;
    int nColumns;
    int nElems;
    double* data;

public:
    // 构造函数
    Matrix(int row, int col): nRows(row), nColumns(col){
        nElems = nRows * nColumns;
        data = new double[nElems];
        for(int i = 0; i < nElems; i++){
            data[i] = 0.0;
        }
    }

    // （深度）复制构造函数
    Matrix(const Matrix& x): nRows(x.nRows), nColumns(x.nColumns), nElems(x.nElems){
        data = new double[nElems];
        for(int i = 0; i < nElems; i++){
            data[i] = x.data[i];
        }
    }

    // 析构函数
    ~Matrix(){
        delete[] data;
    }

    // （深度）重载赋值运算符
    Matrix& operator=(const Matrix& x){
        if(this != &x){
            delete[] data;
            nRows = x.nRows;
            nColumns = x.nColumns;
            nElems = x.nElems;
            data = new double[nElems];
            for(int i = 0; i < nElems; i++){
                data[i] = x.data[i];
            }
        }
        return *this;
    }

    // 获取矩阵元素个数
    int nElements() const{
        return nElems;
    }
    
    // 矩阵赋值：（行，列，值）
    void set(int row, int col, double value){
        data[row * nColumns + col] = value;
    }
    // 获取矩阵某一行某一列的值
    double get(int row, int col) const{
        return data[row * nColumns + col];
    }

    // 矩阵相加函数
    void add(const Matrix& m){
        for(int i = 0; i < nElems; i++){
            data[i] += m.data[i];
        }
    }

    // 矩阵相减函数
    void sub(const Matrix& m){
        for(int i = 0; i < nElems; i++){
            data[i] -= m.data[i];
        }
    }

    int getnRows() const
    {
        return nRows;
    }

    int getnColumns() const
    {
        return nColumns;
    }
};

int main(){
    Matrix m1(2,3);
    Matrix m2(2,3);
    Matrix m3(2,3);

    
    m1.set(0,0,1);
    m1.set(0,1,5);
    m1.set(0,2,9);
    m1.set(1,0,7);
    m1.set(1,1,3);
    m1.set(1,2,2);

    m2.set(0,0,9);
    m2.set(0,1,2);
    m2.set(0,2,5);
    m2.set(1,0,3);
    m2.set(1,1,1);
    m2.set(1,2,1);

    m3.set(0,0,4);
    m3.set(0,1,5);
    m3.set(0,2,2);
    m3.set(1,0,4);
    m3.set(1,1,9);
    m3.set(1,2,3);
    
    int nColumns = m1.getnColumns();
    int nRows = m1.getnRows();

    cout << "矩阵m1：" << endl;
    for (int row = 0; row < nRows; row++) {
        for (int col = 0; col < nColumns; col++) {
            cout << m1.get(row, col) << " ";
        }
        cout << endl;
    }
    
    cout << "矩阵m2：" << endl;
    for (int row = 0; row < nRows; row++) {
        for (int col = 0; col < nColumns; col++) {
            cout << m2.get(row, col) << " ";
        }
        cout << endl;
    }

    cout << "矩阵m3：" << endl;
    for (int row = 0; row < nRows; row++) {
        for (int col = 0; col < nColumns; col++) {
            cout << m3.get(row, col) << " ";
        }
        cout << endl;
    }

    cout << "m1的元素个数：" << m1.nElements() << endl;
    cout << "m1所占的存储空间大小为" << sizeof(double) * m1.nElements() << "个字节" << endl;

    cout << "m1的第一行：" << endl;
    for (int col = 0; col < nColumns; col++) {
        cout << m1.get(0, col) << " ";
    }
    cout << endl;

    cout << "m1的第二列：" << endl;
    for (int row = 0; row < nRows; row++) {
        cout << m1.get(row, 1) << endl;
    }

    m1.add(m2);
    cout << "m1加m2：" << endl;
    for (int row = 0; row < nRows; row++) {
        for (int col = 0; col < nColumns; col++) {
            cout << m1.get(row, col) << " ";
        }
        cout << endl;
    }

    m2.sub(m3);
    cout << "m2减m3：" << endl;
    for (int row = 0; row < nRows; row++) {
        for (int col = 0; col < nColumns; col++) {
            cout << m2.get(row, col) << " ";
        }
        cout << endl;
    }

    return 0;
}