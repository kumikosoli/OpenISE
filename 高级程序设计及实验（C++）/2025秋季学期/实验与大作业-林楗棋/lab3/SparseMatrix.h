#ifndef SPARSE_MATRIX_H
#define SPARSE_MATRIX_H

#include <vector>
#include <iostream>
#include "matrix.h"
struct NonzeroElements {
    int row;
    int col;
    float value;
};

class SparseMatrix {
public:
    SparseMatrix(int rows, int cols);
    SparseMatrix(const SparseMatrix& other);
    SparseMatrix(const Matrix& other);
    SparseMatrix& operator =(const SparseMatrix& other);
    SparseMatrix& operator =(const Matrix& other);
    ~SparseMatrix();
    Matrix toDenseMatrix() const;

    void add(const SparseMatrix& other);
    void sub(const SparseMatrix& other);
    void add(const Matrix& other);
    void sub(const Matrix& other);

    SparseMatrix operator +(const SparseMatrix& other) const;
    SparseMatrix operator -(const SparseMatrix& other) const;
    SparseMatrix operator +(const Matrix& other) const;
    SparseMatrix operator -(const Matrix& other) const;
    friend std::ostream& operator <<(std::ostream& os, const SparseMatrix& matrix);

    float get(int row, int col) const;
    void set(int row, int col, float value);
    void print() const;

private:
    int rows;
    int cols;
    std::vector<NonzeroElements> elements;
};

#endif // SPARSE_MATRIX_H