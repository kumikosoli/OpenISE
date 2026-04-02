#include "SparseMatrix.h"
#include "matrix.h"
#include <iostream>
#include <algorithm>

Matrix SparseMatrix::toDenseMatrix() const {
    Matrix* dense = new Matrix(rows, cols);
    for (const auto& elem : elements) {
        dense->set(elem.row, elem.col, elem.value);
    }
    return *dense;
}

SparseMatrix::SparseMatrix(int rows, int cols) : rows(rows), cols(cols) {
    elements = std::vector<NonzeroElements>();
}

SparseMatrix::SparseMatrix(const SparseMatrix& other) : rows(other.rows), cols(other.cols) {
    std::vector<NonzeroElements> ele = std::vector<NonzeroElements>();
    for (const auto& elem : other.elements) {
        ele.push_back(elem);
    }
    elements = ele;
}

SparseMatrix::SparseMatrix(const Matrix& other) : rows(other.getRows()), cols(other.getCols()) {
    elements = std::vector<NonzeroElements>();
    for (int i = 0;i < rows;i++) {
        for (int j = 0;j < cols;j++) {
            float value = other.get(i, j);
            if (value != 0) {
                NonzeroElements elem = {i, j, value};
                elements.push_back(elem);
            }
        }
    }
}

SparseMatrix& SparseMatrix::operator=(const SparseMatrix& other) {
    if (this != &other) {
        rows = other.rows;
        cols = other.cols;
        elements.clear();
        for (const auto& element : other.elements) {
            NonzeroElements elem = {element.row, element.col, element.value};
            elements.push_back(elem);
        }
    }
    return *this;
}

SparseMatrix& SparseMatrix::operator=(const Matrix& other) {
    rows = other.getRows();
    cols = other.getCols();
    elements.clear();
    for (int i = 0;i < rows;i++) {
        for (int j = 0;j < cols;j++) {
            float value = other.get(i, j);
            if (value != 0) {
                NonzeroElements elem = {i, j, value};
                elements.push_back(elem);
            }
        }
    }
    return *this;
}

SparseMatrix::~SparseMatrix() {
    elements.clear();
}

void SparseMatrix::add(const SparseMatrix& other) {
    Matrix self = this->toDenseMatrix();
    Matrix oth = other.toDenseMatrix();
    self.add(oth);
    *this = SparseMatrix(self);
}

void SparseMatrix::sub(const SparseMatrix& other) {
    Matrix self = this->toDenseMatrix();
    Matrix oth = other.toDenseMatrix();
    self.sub(oth);
    *this = SparseMatrix(self);
}

void SparseMatrix::add(const Matrix& other) {
    Matrix self = this->toDenseMatrix();
    self.add(other);
    *this = SparseMatrix(self);
}

void SparseMatrix::sub(const Matrix& other) {
    Matrix self = this->toDenseMatrix();
    self.sub(other);
    *this = SparseMatrix(self);
}

SparseMatrix SparseMatrix::operator+(const SparseMatrix& other) const {
    Matrix self = this->toDenseMatrix();
    Matrix oth = other.toDenseMatrix();
    Matrix result = self + oth;
    return SparseMatrix(result);
}

SparseMatrix SparseMatrix::operator-(const SparseMatrix& other) const {
    Matrix self = this->toDenseMatrix();
    Matrix oth = other.toDenseMatrix();
    Matrix result = self - oth;
    return SparseMatrix(result);
}

SparseMatrix SparseMatrix::operator+(const Matrix& other) const {
    Matrix self = this->toDenseMatrix();
    Matrix result = self + other;
    return SparseMatrix(result);
}

SparseMatrix SparseMatrix::operator-(const Matrix& other) const {
    Matrix self = this->toDenseMatrix();
    Matrix result = self - other;
    return SparseMatrix(result);
}

float SparseMatrix::get(int row, int col) const {
    for (const auto& elem : elements) {
        if (elem.row == row && elem.col == col) {
            return elem.value;
        }
    }
    return 0.0f;
}

void SparseMatrix::set(int row, int col, float value) {
    std::vector<NonzeroElements> copy = std::vector<NonzeroElements>();
    bool found = false;
    for (const auto& elem : elements) {
        if (elem.row == row && elem.col == col) {
            found = true;
            if (value != 0) {
                NonzeroElements newElem = {row, col, value};
                copy.push_back(newElem);
            }
        } else {
            copy.push_back(elem);
        }
    }
    if (!found && value != 0) {
        NonzeroElements newElem = {row, col, value};
        copy.push_back(newElem);
    }
    this->elements = copy;
}

void SparseMatrix::print() const {
    Matrix dense = this->toDenseMatrix();
    dense.display();
}

std::ostream& operator<<(std::ostream& os, const SparseMatrix& matrix) {
    Matrix dense = matrix.toDenseMatrix();
    for (int i = 0; i < dense.getRows(); ++i) {
        for (int j = 0; j < dense.getCols(); ++j) {
            os << dense.get(i, j) << " ";
        }
        os << std::endl;
    }
    return os;
}