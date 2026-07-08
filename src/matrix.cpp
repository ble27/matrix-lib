/**
 * src/matrix.cpp
 * author: Bao Le
 */

#include "../include/matrix.hpp"
#include <stdexcept>
#include <iostream>
#include <iomanip>
#include <optional>

//==============================
// Constructors
//==============================

Matrix::Matrix(size_t rows, size_t cols)
    : rows_(rows), cols_(cols), data_(rows * cols, 0.0) {}

Matrix::Matrix(size_t rows, size_t cols, std::vector<double> ip)
    : rows_(rows), cols_(cols), data_(rows * cols) {
    if (ip.size() != rows * cols)
        throw std::runtime_error("Matrix input size mismatches with matrix shape\n");
    for (size_t i = 0; i < ip.size(); i++)
        data_[i] = ip[i];
}

//==============================
// Element Access
//==============================

// Read
double Matrix::operator()(size_t r, size_t c) const {
    if (r >= rows_ || c >= cols_)
        throw std::runtime_error("Matrix index out of range\n");
    return data_[r * cols_ + c];
}

// Write
double& Matrix::operator()(size_t r, size_t c) {
    if (r >= rows_ || c >= cols_)
        throw std::runtime_error("Matrix index out of range\n");
    return data_[r * cols_ + c];
}

//==============================
// Shape
//==============================

std::tuple<size_t, size_t> Matrix::shape() const noexcept {
    return std::make_tuple(rows(), cols());
}

//==============================
// Comparison
//==============================

bool Matrix::operator==(const Matrix& other) const {
    if ((*this).shape() != other.shape())
        return false;
    for (size_t i = 0; i < data_.size(); i++)
        if (data_[i] != other.data_[i])
            return false;
    return true;
}

bool Matrix::operator!=(const Matrix& other) const {
    if ((*this).shape() != other.shape())
        return true;
    for (size_t i = 0; i < data_.size(); i++)
        if (data_[i] != other.data_[i])
            return true;
    return false;
}

//==============================
// Arithmetic
//==============================

// Matrix multiplication
Matrix Matrix::operator*(const Matrix& other) const {
    if (cols_ != other.rows_)
        throw std::runtime_error("Invalid matrix multiplication due to row-column mismatch\n");

    Matrix res(rows_, other.cols_);
    for (size_t i = 0; i < rows_; i++)
        for (size_t j = 0; j < other.cols_; j++)
            for (size_t k = 0; k < cols_; k++)
                res(i, j) += (*this)(i, k) * other(k, j);
    return res;
}

// Scalar multiplication
Matrix Matrix::operator*(double factor) const {
    Matrix res = *this;
    res *= factor;
    return res;
}

// In-place scalar multiplication
Matrix& Matrix::operator*=(double factor) {
    for (size_t i = 0; i < data_.size(); i++)
        data_[i] *= factor;
    return *this;
}

// Elementwise multiplication
Matrix Matrix::elementwise_multiply(const Matrix& other) const {
    if ((*this).shape() != other.shape())
        throw std::runtime_error("Dimension mismatch for elementwise multiplication\n");

    Matrix res(rows_, cols_);
    for (size_t i = 0; i < data_.size(); i++)
        res.data_[i] = data_[i] * other.data_[i];
    return res;
}

// Matrix addition
Matrix Matrix::operator+(const Matrix& other) const {
    if ((*this).shape() != other.shape())
        throw std::runtime_error("Invalid matrix addition due to dimension mismatch\n");

    Matrix res = *this;
    res += other;
    return res;
}

// In-place matrix addition
Matrix& Matrix::operator+=(const Matrix& other) {
    if ((*this).shape() != other.shape())
        throw std::runtime_error("Invalid matrix addition due to dimension mismatch\n");

    for (size_t i = 0; i < data_.size(); i++)
        data_[i] += other.data_[i];
    return *this;
}

// Scalar addition
Matrix Matrix::operator+(double scalar) const {
    Matrix res = *this;
    res += scalar;
    return res;
}

// In-place scalar addition
Matrix& Matrix::operator+=(double scalar) {
    for (size_t i = 0; i < data_.size(); i++)
        data_[i] += scalar;
    return *this;
}

// Matrix subtraction
Matrix Matrix::operator-(const Matrix& other) const {
    if ((*this).shape() != other.shape())
        throw std::runtime_error("Invalid matrix subtraction due to dimension mismatch\n");

    Matrix res = *this;
    res -= other;
    return res;
}

// In-place matrix subtraction
Matrix& Matrix::operator-=(const Matrix& other) {
    if ((*this).shape() != other.shape())
        throw std::runtime_error("Invalid matrix subtraction due to dimension mismatch\n");

    for (size_t i = 0; i < data_.size(); i++)
        data_[i] -= other.data_[i];
    return *this;
}

// Scalar subtraction
Matrix Matrix::operator-(double scalar) const {
    Matrix res = *this;
    res -= scalar;
    return res;
}

// In-place scalar subtraction
Matrix& Matrix::operator-=(double scalar) {
    for (size_t i = 0; i < data_.size(); i++)
        data_[i] -= scalar;
    return *this;
}

// Division
Matrix Matrix::operator/(double scalar) const {
    Matrix res = *this;
    res /= scalar;
    return res;
}

// In-place division
Matrix& Matrix::operator/=(double scalar) {
    for (size_t i = 0; i < data_.size(); i++)
        data_[i] /= scalar;
    return *this;
}

// Dot product
double Matrix::dot(const Matrix& other) const {
    if ((*this).shape() != other.shape())
        throw std::runtime_error("Dimension mismatch incompatible for matrix dot product\n");

    double total = 0.0;
    for (size_t i = 0; i < data_.size(); i++)
        total += data_[i] * other.data_[i];
    return total;
}

//==============================
// Reductions
//==============================

double Matrix::sum() const {
    double total = 0.0;
    for (size_t i = 0; i < data_.size(); i++)
        total += data_[i];
    return total;
}

Matrix Matrix::sum(int axis) const {
    Matrix res = (axis == 0) ? Matrix(rows_, 1) : Matrix(1, cols_);
    if (axis == 0) {
        for (size_t r = 0; r < rows_; r++)
            for (size_t c = 0; c < cols_; c++)
                res(r, 0) += (*this)(r, c);
        return res;
    }
    for (size_t c = 0; c < cols_; c++)
        for (size_t r = 0; r < rows_; r++)
            res(0, c) += (*this)(r, c);
    return res;
}

double Matrix::mean() const {
    return sum() / data_.size();
}

Matrix Matrix::mean(int axis) const {
    Matrix res = (axis == 0) ? Matrix(rows_, 1) : Matrix(1, cols_);
    if (axis == 0) {
        for (size_t r = 0; r < rows_; r++) {
            double s = 0.0;
            for (size_t c = 0; c < cols_; c++)
                s += (*this)(r, c);
            res(r, 0) = s / cols_;
        }
        return res;
    }
    for (size_t c = 0; c < cols_; c++) {
        for (size_t r = 0; r < rows_; r++)
            res(0, c) += (*this)(r, c);
        res(0, c) /= rows_;
    }
    return res;
}

double Matrix::max() const {
    double cur_max = data_[0];
    for (size_t i = 1; i < data_.size(); i++)
        if (data_[i] > cur_max)
            cur_max = data_[i];
    return cur_max;
}

Matrix Matrix::max(int axis) const {
    Matrix res = (axis == 0) ? Matrix(rows_, 1) : Matrix(1, cols_);
    if (axis == 0) {
        for (size_t r = 0; r < rows_; r++) {
            double cur_max = (*this)(r, 0);
            for (size_t c = 1; c < cols_; c++)
                if ((*this)(r, c) > cur_max)
                    cur_max = (*this)(r, c);
            res(r, 0) = cur_max;
        }
        return res;
    }
    for (size_t c = 0; c < cols_; c++) {
        double cur_max = (*this)(0, c);
        for (size_t r = 1; r < rows_; r++)
            if ((*this)(r, c) > cur_max)
                cur_max = (*this)(r, c);
        res(0, c) = cur_max;
    }
    return res;
}

double Matrix::min() const {
    double cur_min = data_[0];
    for (size_t i = 1; i < data_.size(); i++)
        if (data_[i] < cur_min)
            cur_min = data_[i];
    return cur_min;
}

Matrix Matrix::min(int axis) const {
    Matrix res = (axis == 0) ? Matrix(rows_, 1) : Matrix(1, cols_);
    if (axis == 0) {
        for (size_t r = 0; r < rows_; r++) {
            double cur_min = (*this)(r, 0);
            for (size_t c = 1; c < cols_; c++)
                if ((*this)(r, c) < cur_min)
                    cur_min = (*this)(r, c);
            res(r, 0) = cur_min;
        }
        return res;
    }
    for (size_t c = 0; c < cols_; c++) {
        double cur_min = (*this)(0, c);
        for (size_t r = 1; r < rows_; r++)
            if ((*this)(r, c) < cur_min)
                cur_min = (*this)(r, c);
        res(0, c) = cur_min;
    }
    return res;
}

//==============================
// Norms
//==============================

// Absolute sum of all elements
double Matrix::l1_elementwise_norm() const {
    double total = 0.0;
    for (size_t i = 0; i < data_.size(); i++)
        total += std::abs(data_[i]);
    return total;
}

// Max absolute column sum
double Matrix::l1_induced_norm() const {
    double max_col_sum = 0.0;
    for (size_t c = 0; c < cols_; c++) {
        double col_sum = 0.0;
        for (size_t r = 0; r < rows_; r++)
            col_sum += std::abs(at(r, c));
        max_col_sum = std::max(max_col_sum, col_sum);
    }
    return max_col_sum;
}

// Max absolute row sum
double Matrix::inf_norm() const {
    double max_row_sum = 0.0;
    for (size_t r = 0; r < rows_; r++) {
        double row_sum = 0.0;
        for (size_t c = 0; c < cols_; c++)
            row_sum += std::abs(at(r, c));
        max_row_sum = std::max(max_row_sum, row_sum);
    }
    return max_row_sum;
}

// Square root of sum of all squared elements (Frobenius)
double Matrix::l2_norm() const {
    double total = 0.0;
    for (size_t i = 0; i < data_.size(); i++)
        total += data_[i] * data_[i];
    return std::sqrt(total);
}

//==============================
// Structural
//==============================

Matrix Matrix::transpose() const {
    Matrix tp(cols_, rows_);
    for (size_t c = 0; c < cols_; c++)
        for (size_t r = 0; r < rows_; r++)
            tp(c, r) = (*this)(r, c);
    return tp;
}

Matrix Matrix::slice(size_t r0, size_t r1, size_t c0, size_t c1) const {
    if (r1 < r0 || c1 < c0 || r1 >= rows_ || c1 >= cols_)
        throw std::runtime_error("Invalid dimension for matrix slicing\n");

    Matrix res(r1 - r0 + 1, c1 - c0 + 1);
    for (size_t r = r0; r <= r1; r++)
        for (size_t c = c0; c <= c1; c++)
            res(r - r0, c - c0) = (*this)(r, c);
    return res;
}

//==============================
// Application
//==============================

Matrix Matrix::apply(std::function<double(double)> func) const {
    Matrix res(rows_, cols_);
    for (size_t i = 0; i < data_.size(); i++)
        res.data_[i] = func(data_[i]);
    return res;
}

Matrix& Matrix::apply_(std::function<double(double)> func) {
    for (size_t i = 0; i < data_.size(); i++)
        data_[i] = func(data_[i]);
    return *this;
}

//==============================
// Static Factories
//==============================

Matrix Matrix::zeros(size_t rows, size_t cols) {
    return Matrix(rows, cols);
}

Matrix Matrix::ones(size_t rows, size_t cols) {
    Matrix res(rows, cols);
    for (size_t i = 0; i < res.data_.size(); i++)
        res.data_[i] = 1.0;
    return res;
}

Matrix Matrix::identity(size_t n) {
    Matrix res(n, n);
    for (size_t i = 0; i < res.data_.size(); i += n + 1)
        res.data_[i] = 1.0;
    return res;
}

//==============================
// Utilities
//==============================

void Matrix::fill(double value) {
    for (size_t i = 0; i < data_.size(); i++) {
        data_[i] = value;
    }
}

Matrix Matrix::clip(double min, double max) {
    Matrix res = *this;
    if (min > max)
        throw std::runtime_error("Minimum value less than maximum value\n");

    for (size_t i = 0; i < data_.size(); i++) {
        if (res.data_[i] <= min) {
            res.data_[i] = min;
        }
        if (res.data_[i] >= max) {
            res.data_[i] = max;
        }
    }
    return res;
}

Matrix Matrix::reshape(double row, double col) const {
    if (row * col != rows_ * cols_) 
        throw std::runtime_error("Reshape size mistmatch - element count must match\n");

    Matrix res(row, col);
    res.data_ = (*this).data_;
    return res;
}

// 1 * (rows_ * cols_) matrix
Matrix Matrix::flatten() const {
    Matrix res(1, rows_ * cols_);
    res.data_ = (*this).data_;
    return res;
}


//==============================
// Output
//==============================

std::ostream& operator<<(std::ostream& os, const Matrix& m) {
    os << '\n';
    for (size_t r = 0; r < m.rows(); r++) {
        os << "[";
        for (size_t c = 0; c < m.cols(); c++) {
            os << std::fixed << std::setprecision(2) << m(r, c);
            if (c < m.cols() - 1)
                os << ", ";
        }
        os << "]\n";
    }
    os << '\n';
    return os;
}