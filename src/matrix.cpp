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

    for (size_t i = 0; i < ip.size() ; i++) {
        data_[i] = ip[i];
    }
};

// Read - element access
double Matrix::operator()(size_t r, size_t c) const {
    if (r >= rows_ || c >= cols_) 
        throw std::runtime_error("Matrix index out of range\n");
    return data_[r * cols_ + c];    
}

// Modify - element access
double& Matrix::operator()(size_t r, size_t c) {
    if (r >= rows_ || c >= cols_) // zero indexing means the number has to be 1 less than actual
        throw std::runtime_error("Matrix index out of ranage\n");
    return data_[r * cols_ + c];    
}

// Matrix multiplication
Matrix Matrix::operator*(const Matrix& other) const {
    if (cols_ != other.rows_) 
        throw std::runtime_error("Invalid matrix multiplication due to row-column mismatch\n");

    Matrix res(rows_, other.cols_);
    for (size_t i = 0; i < rows_; i++) {
        for (size_t j = 0; j < other.cols_; j++) {
            for (size_t k = 0; k < cols_; k++) {
                res(i, j) += (*this)(i, k) * other(k, j);
            }
        }
    }
    return res;
}

// Addition
Matrix Matrix::operator+(const Matrix& other) const {
    if ((*this).shape() != other.shape()) 
        throw std::runtime_error("Invalid matrix addition due to dimension mismatch\n");

    Matrix res(rows_, cols_);
    for (int r = 0; r < rows_; r++) {
        for (size_t c = 0; c < cols_; c++) {
            res(r, c) = (*this)(r, c) + other(r, c);
        }
    }
    return res;
}

// Subtraction
Matrix Matrix::operator-(const Matrix& other) const {
    if ((*this).shape() != other.shape()) 
        throw std::runtime_error("Invalid matrix addition due to dimension mismatch\n");

    Matrix res(rows_, cols_);
    for (int r = 0; r < rows_; r++) {
        for (size_t c = 0; c < cols_; c++) {
            res(r, c) = (*this)(r, c) - other(r, c);
        }
    }
    return res;
}

// Division
Matrix Matrix::operator/(double scalar) const { 
    Matrix res(rows_, cols_);
    for (size_t i = 0; i < data_.size(); i++) {
        res.data_[i] /= scalar;
    }
    return res;
}

// Scalar multiplication
Matrix Matrix::operator*(double factor) const {
    Matrix res(rows(), cols());
    for (size_t r = 0; r < rows_; r++) {
        for (size_t c = 0; c < cols_; c++) {
            res(r, c) = (*this)(r, c) * factor;
        }
    }
    return res;
}

// In-place addition
Matrix& Matrix::operator+=(const Matrix& other) {
    if ((*this).shape() != other.shape()) 
        throw std::runtime_error("Invalid matrix addition due to dimension mismatch\n");

     for (int r = 0; r < rows_; r++) {
        for (size_t c = 0; c < cols_; c++) {
            (*this)(r, c) = (*this)(r, c) + other(r, c);
        }
    }
    return *this;
}

// In-place subtraction
Matrix& Matrix::operator-=(const Matrix& other) {
    if ((*this).shape() != other.shape()) 
        throw std::runtime_error("Invalid matrix addition due to dimension mismatch\n");
     for (int r = 0; r < rows_; r++) {
        for (size_t c = 0; c < cols_; c++) {
            (*this)(r, c) = (*this)(r, c) - other(r, c);
        }
    }
    return *this;
}

// In-place multiplication
Matrix& Matrix::operator*=(double factor) {
    for (size_t i = 0; i < data_.size(); i++) {
        data_[i] *= factor;
    }
    return *this;
}

// In-place division
Matrix& Matrix::operator/=(double scalar) {
    for (size_t i = 0; i < data_.size(); i++) {
        data_[i] /= scalar;
    }
    return *this;
}

// Matrix shape
std::tuple<size_t, size_t> Matrix::shape() const {
    return std::make_tuple(rows(), cols());
}

// Comparison
bool Matrix::operator==(const Matrix& other) const {
    if ((*this).shape() != other.shape()) 
        return false;
    for (size_t i = 0; i < data_.size(); i++) {
        if (data_[i] != other.data_[i]) 
            return false;
    }
    return true;
}

bool Matrix::operator!=(const Matrix& other) const {
    if ((*this).shape() != other.shape()) 
        return true;
    for (size_t i = 0; i < data_.size(); i++) {
        if (data_[i] != other.data_[i]) 
            return true;
    }
    return false;
}

// Print
std::ostream& operator<<(std::ostream& os, const Matrix& m) {
    os << '\n';
    for (size_t i = 0; i < m.rows(); i++) {
        os << "[";
        for (size_t j = 0; j < m.cols(); j++) {
            os << std::fixed << std::setprecision(2) << m(i, j);
            if (j < m.cols() - 1) 
                os << ", ";
        }
        os << "]";
        os << '\n';
    }   
    os << '\n';
    return os;
}