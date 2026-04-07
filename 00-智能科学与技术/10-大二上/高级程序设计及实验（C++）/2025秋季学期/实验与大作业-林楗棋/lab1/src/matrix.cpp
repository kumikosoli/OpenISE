#include "matrix.h"
#include <iostream>
#include <vector>

Matrix::Matrix(int r, int c, std::vector<std::vector<float>> d) {
    rows = r;
    cols = c;
    if (!d.empty()) {
        if (static_cast<int>(d.size()) != r || static_cast<int>(d[0].size()) != c) {
            std::cerr << "提供的矩阵与行列信息不对应！" << std::endl;
            data.assign(r, std::vector<float>(c, 0.0f));
        } else {
            data = std::move(d);
        }
    } else {
        // 若未提供数据，则初始化为 r x c 的零矩阵
        data.assign(r, std::vector<float>(c, 0.0f));
    }
}

Matrix::Matrix(const Matrix& copy) {
    rows = copy.rows;
    cols = copy.cols;
    data = copy.data;
}

Matrix::~Matrix() {
    data.clear();
}

std::vector<std::vector<float>> Matrix::getData() {
    return data;
}

void Matrix::add(const Matrix& other) {
    if (rows != other.rows || cols != other.cols) {
        std::cerr << "矩阵加法维度不对应！" << std::endl;
        return;
    }
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            data[i][j] += other.data[i][j];
        }
    }
}

void Matrix::display() {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            std::cout << data[i][j] << ' ';
        }
        std::cout << ' ' << std::endl;
    }
}

std::pair<int, int> Matrix::size() {
    return std::pair<int, int> {rows, cols};
}

std::vector<float> Matrix::getLine(int r) {
    return data[r];
}

std::vector<float> Matrix::getColumn(int c) {
    std::vector<float> re(rows);
    for (int i = 0;i < rows;i++) {
        re[i] = data[i][c];
    }
    return re;
}

std::vector<std::vector<float>> mul(Matrix& a, Matrix& b) {
    auto [a_rows, a_cols] = a.size();
    auto [b_rows, b_cols] = b.size();
    std::vector<std::vector<float>> result(a_rows, std::vector<float>(b_cols, 0.0));
    if (a_cols != b_rows) {
        std::cerr << "矩阵乘法维度不对应！" << std::endl;
        return result;
    }
    auto a_data = a.getData();
    auto b_data = b.getData();
    for (int i = 0; i < a_rows; ++i) {
        for (int j = 0; j < b_cols; ++j) {
            for (int k = 0; k < a_cols; ++k) {
                result[i][j] += a_data[i][k] * b_data[k][j];
            }
        }
    }
    return result;
}
