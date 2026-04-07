#include <utility>
#include <vector>
#ifndef MATRIX_H
#define MATRIX_H

class Matrix {
    int rows, cols;
    std::vector<std::vector<float>> data;
public:
    Matrix(int r, int c, std::vector<std::vector<float>> d);
    Matrix(const Matrix& copy);
    ~Matrix();
    void add(const Matrix& other);
    void display();
    std::pair<int, int> size();
    std::vector<float> getLine(int r);
    std::vector<float> getColumn(int c);
    std::vector<std::vector<float>> getData();
    friend std::vector<std::vector<float>> mul(Matrix& a, Matrix& b);
};

#endif
