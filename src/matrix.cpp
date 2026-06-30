/**
 * src/matrix.cpp
 * author: Bao Le
 */

#include "../include/matrix.hpp"
#include <stdexcept>
#include <iostream>
#include <iomanip> 
#include <optional>

Matrix::Matrix(size_t rows, size_t cols) 
    : rows_(rows), cols_(cols), data_(rows* cols, 0.0) {} 

Matrix::Matrix(size_t rows, size_t cols, std::vector<double> ip) 
    : rows_(rows), cols_(cols), data_(rows * cols) {
    if (ip.size() != rows * cols) 
        throw std::runtime_error("Matrix input size mismatches with matrix shape\n");

    for (int i = 0; i < ip.size() ; i++) {
        data_[i] = ip[i];
    }
};

// Read - element access
double Matrix::operator()(size_t r, size_t c) const {
    if (r > rows_ || c > cols_) 
        throw std::runtime_error("Matrix index out of range\n");
    return data_[r * cols_ + c];    
}

// Modify - element access
double& Matrix::operator()(size_t r, size_t c) {
    if (r > rows_ || c > cols_)
        throw std::runtime_error("Matrix index out of ranage\n");
    return data_[r * cols_ + c];    
}

// Matrix multiply 
Matrix Matrix::operator*(const Matrix& other) const {
    if (rows_ != other.rows_) 
        throw std::runtime_error("Invalid matrix multiplication due to row-column mismatch\n");

    Matrix res(rows_, other.cols_);
    for (int i = 0; i < rows_; i++) {
        for (int j = 0; j < other.cols_; j++) {
            for (int k = 0; k < cols_; k++) {
                res(i, j) = (*this)(i, k) * other(k, j);
            }
        }
    }
    return res;
}

// Print
void Matrix::print() const {
    std::cout << '\n';
    for (int i = 0; i < rows_; i++) {
        std::cout << "[";
        for (int j = 0; j < cols_; j++) {
            std::cout << std::fixed << std::setprecision(2) << (*this)(i, j);
            if (j < cols_ - 1) 
                std::cout << ", ";
        }
        std::cout << "]";
        std::cout << '\n';
    }   
    std::cout << '\n';
}

int main() {
    Matrix test(2, 3, std::vector<double>{1,2,3,4,5,6});
    test.print();
    return 0;
}