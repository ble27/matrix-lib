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
    : rows_(rows), cols_(cols), data_(rows * cols, 0.0) {} 

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
    for (size_t r = 0; r < rows_; r++) {
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
    for (size_t r = 0; r < rows_; r++) {
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

// In-place addition expanded
Matrix& Matrix::operator+(const Matrix& other) {
    if ((*this).shape() != other.shape()) 
        throw std::runtime_error("Invalid matrix addition due to dimension mismatch\n");

     for (size_t r = 0; r < rows_; r++) {
        for (size_t c = 0; c < cols_; c++) {
            (*this)(r, c) = (*this)(r, c) + other(r, c);
        }
    }
    return *this;
}

// In-place addition
Matrix& Matrix::operator+=(const Matrix& other) {
    if ((*this).shape() != other.shape()) 
        throw std::runtime_error("Invalid matrix addition due to dimension mismatch\n");

     for (size_t r = 0; r < rows_; r++) {
        for (size_t c = 0; c < cols_; c++) {
            (*this)(r, c) = (*this)(r, c) + other(r, c);
        }
    }
    return *this;
}

// In-place subtraction expanded
Matrix& Matrix::operator-(const Matrix& other) {
    if ((*this).shape() != other.shape()) 
        throw std::runtime_error("Invalid matrix addition due to dimension mismatch\n");

     for (size_t r = 0; r < rows_; r++) {
        for (size_t c = 0; c < cols_; c++) {
            (*this)(r, c) = (*this)(r, c) - other(r, c);
        }
    }
    return *this;
}

// In-place subtraction
Matrix& Matrix::operator-=(const Matrix& other) {
    if ((*this).shape() != other.shape()) 
        throw std::runtime_error("Invalid matrix addition due to dimension mismatch\n");

     for (size_t r = 0; r < rows_; r++) {
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

// In-place division expanded
Matrix& Matrix::operator/(double scalar) {
    for (size_t i = 0; i < data_.size(); i++) {
        data_[i] /= scalar;
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

// Reductions
double Matrix::sum() const {
    double total = 0;
    for (size_t i = 0; i < data_.size(); i++) {
        total += data_[i];
    }
    return total;
};

Matrix Matrix::sum(int axis) const {
    // 0 = across rows, 1 = across cols
    Matrix res = (axis == 0) ? Matrix(rows_, 1) : Matrix(1, cols_);
    // Across rows res(i, 0) -> row-major
    if (axis == 0) {
        for (size_t r = 0; r < rows_; r++) {
            for (size_t c = 0; c < cols_; c++) {
                res(r, 0) += (*this)(r, c);
            }
        }
        return res;
    }
    // Across cols res(0, c) -> col-major
    else {
       for (size_t c = 0; c < cols_; c++) {
            for (size_t r = 0; r < rows_; r++) {
                res(0, c) += (*this)(r, c);
            } 
        }
        return res;
    }
};

double Matrix::mean() const {
    double total = 0.0;
    for (size_t i = 0; i < data_.size(); i++) {
        total += data_[i];
    }
    return total /= data_.size();
}

Matrix Matrix::mean(int axis) const {
    // 0 = across rows, 1 = across cols
    Matrix res = (axis == 0) ? Matrix(rows_, 1) : Matrix(1, cols_);
    // Across rows res(i, 0) -> row-major
    if (axis == 0) {
        for (size_t r = 0; r < rows_; r++) {
            double sum = 0.0;
            for (size_t c = 0; c < cols_; c++) {
                sum += (*this)(r, c);
            }
            res(r, 0) = sum / cols_;
        }
        return res;
    }
    // Across cols res(0, c) -> col-major
    else {
       for (size_t c = 0; c < cols_; c++) {
            for (size_t r = 0; r < rows_; r++) {
                res(0, c) += (*this)(r, c);
            } 
            res(0, c) /= rows_;
        }
        return res;
    }
};

double Matrix::max() const {
    double max = data_[0];
    for (size_t i = 1; i < data_.size(); i++) {
        if (data_[i] > max) 
            max = data_[i];
    }
    return max;
};

Matrix Matrix::max(int axis) const {
    Matrix res = (axis == 0) ? Matrix(rows_, 1) : Matrix(1, cols_);
    // Across rows
    if (axis == 0) {
        for (size_t r = 0; r < rows_; r++) {
            double cur_max = (*this)(r, 0); 
            for (size_t c = 1; c < cols_; c++) {
                if ((*this)(r, c) > cur_max)
                    cur_max = (*this)(r, c);
            }
            res(r, 0) = cur_max;
        }
        return res;
    }
    // Across cols
    else {
        for (size_t c = 0; c < cols_; c++) {
            double cur_max = (*this)(0, c);
            for (size_t r = 1; r < rows_; r++) {
                if ((*this)(r, c) > cur_max)
                    cur_max = (*this)(r, c);
            }
            res(0, c) = cur_max;
        }
        return res;
    }
};

double Matrix::min() const {
    double cur_min = data_[0];
    for (size_t i = 1; i < data_.size(); i++) {
        if (data_[i] < cur_min) 
            cur_min = data_[i];
    }
    return cur_min;
};

Matrix Matrix::min(int axis) const {
    Matrix res = (axis == 0) ? Matrix(rows_, 1) : Matrix(1, cols_);
    // Across rows
    if (axis == 0) {
        for (size_t r = 0; r < rows_; r++) {
            double cur_min = (*this)(r, 0); 
            for (size_t c = 1; c < cols_; c++) {
                if ((*this)(r, c) < cur_min)
                    cur_min = (*this)(r, c);
            }
            res(r, 0) = cur_min;
        }
        return res;
    }
    // Across cols
    else {
        for (size_t c = 0; c < cols_; c++) {
            double cur_min = (*this)(0, c);
            for (size_t r = 1; r < rows_; r++) {
                if ((*this)(r, c) < cur_min)
                    cur_min = (*this)(r, c);
            }
            res(0, c) = cur_min;
        }
        return res;
    }
}

Matrix Matrix::apply(std::function<double(double)> func) {
    Matrix res(rows_, cols_);
    for (size_t i = 0; i < data_.size(); i++) { 
        res.data_[i] = func(data_[i]);
    }
    return res;
}

Matrix& Matrix::apply_(std::function<double(double)> func) {
    for (size_t i = 0; i < data_.size(); i++) {
        (*this).data_[i] = func(data_[i]);
    }
    return *this;
}

Matrix Matrix::transpose() const {
    Matrix tp(cols_, rows_);
    for (size_t c = 0; c < cols_; c++) {
        for (size_t r = 0; r < rows_; r++) {
            tp(c, r) = (*this)(r, c);
        }
    }
    return tp;
}

Matrix Matrix::slice(size_t r0, size_t r1, size_t c0, size_t c1) const {
    if (r1 < r0 || c1 < c0 || r1 >= rows_ || c1 >= cols_) 
        throw std::runtime_error("Invalid dimension for matrix slicing\n");
        
    Matrix res(r1 - r0 + 1, c1 - c0 + 1);
    for (size_t r = r0; r <= r1; r++) {
        for (size_t c = c0; c <= c1; c++) {
            // shift the original coordinate to res's new coordinate 
            res(r - r0, c - c0) = (*this)(r, c);
        }
    }
    return res;
}

//=============================================
// Static methods below have no access to *this 
//=============================================
Matrix Matrix::zeros(size_t rows, size_t cols) {
    return Matrix(rows, cols);
}   

Matrix Matrix::ones(size_t rows, size_t cols) {
    Matrix ones(rows, cols);
    for (size_t i = 0; i < ones.data_.size(); i++) {
        ones.data_[i] = 1.0;
    }
    return ones;
}

Matrix Matrix::identity(size_t n) {
    // n = n x n dimension
    Matrix id(n, n);
    // idx + n + 1 gives the index of 1s entry
    for (size_t i = 0; i < id.data_.size(); i+=n+1) {
        id.data_[i] = 1.0;
    }
    return id;
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