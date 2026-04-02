#include "matrix.h"
#include "iostream"
#include "SparseMatrix.h"

Matrix::Matrix(int rows, int cols) {
    nRows = rows;
    nColumns = cols;
    float** data = new float*[rows];
    for (int i = 0; i < rows; ++i)
        data[i] = new float[cols](); 
    this->data = data;
}

Matrix::Matrix(int rows, int cols, float** value) {
    nRows = rows;
    nColumns = cols;
    data = new float*[rows];
    for (int i = 0; i < rows; i++) {
        data[i] = new float[cols];
        for (int j = 0;j < cols;j++) {
            data[i][j] = value[i][j];
        }
    }   
}

Matrix::Matrix(const Matrix& other) {
    nRows = other.nRows;
    nColumns = other.nColumns;
    data = new float*[nRows];
    for (int i = 0;i < nRows;i++) {
        data[i] = new float[nColumns];
        for (int j = 0;j < nColumns;j++) {
            data[i][j] = other.data[i][j];
        }
    }
}

Matrix& Matrix::operator=(const Matrix& other) {
    if (this != &other) {
        for (int i = 0;i < nRows;i++)
            delete[] data[i];
        delete[] data;

        nRows = other.nRows;
        nColumns = other.nColumns;
        data = new float*[nRows];
        for (int i = 0; i < nRows; i++) {
            data[i] = new float[nColumns];
            for (int j = 0; j < nColumns; j++) {
                data[i][j] = other.data[i][j];
            }        
        }
        return *this;
    }
    return *this; // 如果赋值给自己，直接返回
}

Matrix::~Matrix() {
    for (int i = 0; i < nRows; ++i) {
        delete[] data[i];
    }
    delete[] data;
}

int Matrix::nElements() {
    return nRows * nColumns;
}

int Matrix::size() {
    return nRows * nColumns * sizeof(float);
}

void Matrix::add(const Matrix& other) {
    if (nRows != other.nRows || nColumns != other.nColumns) {
        std::cerr << "矩阵维度不匹配，无法相加" << std::endl;
        return;
    }
    for (int i = 0; i < nRows; ++i) {
        for (int j = 0; j < nColumns; ++j) {
            data[i][j] += other.data[i][j];
        }
    }
}

void Matrix::sub(const Matrix& other) {
    if (nRows != other.nRows || nColumns != other.nColumns) {
        std::cerr << "矩阵维度不匹配，无法相减" << std::endl;
        return;
    }
    for (int i = 0; i < nRows; ++i) {
        for (int j = 0; j < nColumns; ++j) {
            data[i][j] -= other.data[i][j];
        }
    }
}

float* Matrix::getc(int c) {
    if (c < 0 || c >= nColumns) {
        std::cerr << "列索引越界" << std::endl;
        return nullptr;
    }
    float* column = new float[nRows];
    for (int i = 0; i < nRows; ++i) {
        column[i] = data[i][c];
    }
    return column;
}

float* Matrix::getl(int l) {
    if (l < 0 || l >= nRows) {
        std::cerr << "行索引越界" << std::endl;
        return nullptr;
    }
    float* row = new float[nColumns];
    for (int j = 0; j < nColumns; ++j) {
        row[j] = data[l][j];
    }
    return row;
}

void Matrix::set(int r, int c, float v) {
    if (r >= nRows || c >= nColumns) {
        std::cerr << "索引越界" << std::endl;
    }
    data[r][c] = v;
}

float Matrix::get(int r, int c) const {
    if (r >= nRows || c > nColumns) {
        std::cerr << "索引越界" << std::endl;
    }
    return data[r][c];
}

void Matrix::display() {
    for (int i = 0; i < nRows; ++i) {
        for (int j = 0; j < nColumns; ++j) {
            std::cout << data[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

Matrix Matrix::operator +(const Matrix& other) {
    if (nRows != other.nRows || nColumns != other.nColumns) {
        std::cerr << "矩阵维度不匹配，无法相加" << std::endl;
    }

    Matrix result(nRows, nColumns);
    for (int i = 0; i < nRows; ++i) {
        for (int j = 0; j < nColumns; ++j) {
            result.data[i][j] = data[i][j] + other.data[i][j];
        }
    }
    return result;
}

Matrix Matrix::operator -(const Matrix& other) {
    if (nRows != other.nRows || nColumns != other.nColumns) {
        std::cerr << "矩阵维度不匹配，无法相减" << std::endl;
    }

    Matrix result(nRows, nColumns);
    for (int i = 0; i < nRows; ++i) {
        for (int j = 0; j < nColumns; ++j) {
            result.data[i][j] = data[i][j] - other.data[i][j];
        }
    }
    return result;
}

Matrix Matrix::operator *(const Matrix& other) {
    if (nColumns != other.nRows) {
        std::cerr << "矩阵维度不匹配，无法相乘" << std::endl;
    }

    Matrix result(nRows, other.nColumns);
    for (int i = 0; i < nRows; ++i) {
        for (int j = 0; j < other.nColumns; ++j) {
            result.data[i][j] = 0;
            for (int k = 0; k < nColumns; ++k) {
                result.data[i][j] += data[i][k] * other.data[k][j];
            }
        }
    }
    return result;
}

SparseMatrix Matrix::toSparseMatrix() {
    SparseMatrix S(this->nRows, this->nColumns);
    for (int i = 0;i < nRows;i++) {
        for (int j = 0;j < nColumns;j++) {
            float value = this->get(i, j);
            if (value != 0) {
                S.set(i, j, value);
            }
        }
    }
    return S;
}