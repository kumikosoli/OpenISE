#include "Matrix.h"
#include <iostream>

Matrix::Matrix(int size_): size(size_) {
    elements.resize(size * size);
    // initialize to zero
    for (int i = 0; i < size * size; ++i) elements[i] = 0.0;
}

Matrix::~Matrix() {
    elements.clear();
}

void Matrix::setMatrix(const double *values) {
    int n = size * size;
    for (int i = 0; i < n; ++i)
        elements[i] = values[i];
}

void Matrix::printMatrix() const {
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j)
            std::cout << element(i, j) << " ";
        std::cout << std::endl;
    }
}