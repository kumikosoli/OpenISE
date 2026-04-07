#ifndef MATRIX_H
#define MATRIX_H
class SparseMatrix; // 前向声明

class Matrix {
    int nRows, nColumns;
    float** data;
public:
    Matrix(int rows, int cols);
    Matrix(int rows, int cols, float** values);
    Matrix(const Matrix& other);
    Matrix& operator =(const Matrix& other);
    ~Matrix();
    SparseMatrix toSparseMatrix();
    int nElements();
    int size();
    void add(const Matrix& other);
    void sub(const Matrix& other);
    float* getc(int c);
    float* getl(int l);
    void set(int c, int l, float v);
    float get(int c, int l) const;
    void display();
    Matrix operator +(const Matrix& other);
    Matrix operator -(const Matrix& other);
    Matrix operator *(const Matrix& other);
    int getRows() const { return nRows; }
    int getCols() const { return nColumns; }
};
#endif