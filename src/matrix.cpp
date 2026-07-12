/**
 * src/matrix.cpp
 * author: Bao Le
 */

#include "../include/matrix.hpp"
#include <stdexcept>
#include <iostream>
#include <iomanip>
#include <optional>
#include <random>

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

Matrix Matrix::clip(double min, double max) const {
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

Matrix Matrix::reshape(size_t row, size_t col) const {
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
// Stacking
//==============================

Matrix Matrix::hstack(const Matrix& a, const Matrix& b) {
    if (a.rows() != b.rows())
        throw std::runtime_error("Row dimension mismatch - unable to group matrix horizontally\n");

    // both matrices have the same row but different cols
    size_t tot_col = a.cols() + b.cols();
    Matrix res(a.rows(), tot_col);

    for (size_t r = 0; r < a.rows(); r++) {
        size_t cb = 0;
        for (size_t c = 0; c < tot_col; c++) {
            // add b's entries 
            if (c > tot_col - b.cols() - 1) {
                res(r, c) = b(r, cb);
                cb++;
            }
            // add a's entries
            else 
                res(r, c) = a(r, c);
        }
    }
    return res;
}

Matrix Matrix::vstack(const Matrix& a, const Matrix& b) {
    if (a.cols() != b.cols())
        throw std::runtime_error("Column dimension mismatch - unable to group matrix horizontally\n");

    Matrix res(a.rows() + b.rows(), a.cols());
    for (size_t i = 0; i < a.data_.size(); i++) {
        res.data_[i] = a.data_[i];
    }
    for (size_t i = 0; i < b.data_.size(); i++) {
        res.data_[i + a.data_.size()] = b.data_[i];
    }
    return res;
}

//==============================
// Arg Index
//==============================

size_t Matrix::argmax() const {
    size_t idx = 0;
    for (size_t i = 1; i < data_.size(); i++) {
        if (data_[i] > data_[idx]) {
            idx = i;
        }
    }
    return idx;
}   

size_t Matrix::argmin() const {
    size_t idx = 0;
    for (size_t i = 1; i < data_.size(); i++) {
        if (data_[i] < data_[idx]) {
            idx = i;
        }
    }
    return idx;
}

Matrix Matrix::argmax(int axis) const {
    Matrix res = (axis == 0) ? Matrix(rows_, 1) : Matrix(1, cols_);

    // Across rows
    if (axis == 0) {
        for (size_t r = 0; r < rows_; r++) {
            size_t cur_max_col = 0;
            for (size_t c = 1; c < cols_; c++) {
                if ((*this)(r, c) > (*this)(r, cur_max_col)) {
                    cur_max_col = c;
                }
            }
            res(r, 0) = static_cast<double>(cur_max_col); 
        }
        return res;
    }
    // Across cols
    else {
        for (size_t c = 0; c < cols_; c++) {
            size_t cur_max_row = 0;
            for (size_t r = 1; r < rows_; r++) {
                if ((*this)(r, c) > (*this)(cur_max_row, c)) {
                    cur_max_row = r;
                }
            }
            res(0, c) = static_cast<double>(cur_max_row); 
        }
        return res;
    }
} 

Matrix Matrix::argmin(int axis) const {
    Matrix res = (axis == 0) ? Matrix(rows_, 1) : Matrix(1, cols_);

    // Across rows
    if (axis == 0) {
        for (size_t r = 0; r < rows_; r++) {
            size_t cur_min_col = 0;
            for (size_t c = 1; c < cols_; c++) {
                if ((*this)(r, c) < (*this)(r, cur_min_col)) {
                    cur_min_col = c;
                }
            }
            res(r, 0) = static_cast<double>(cur_min_col); 
        }
        return res;
    }
    // Across cols
    else {
        for (size_t c = 0; c < cols_; c++) {
            size_t cur_min_row = 0;
            for (size_t r = 1; r < rows_; r++) {
                if ((*this)(r, c) < (*this)(cur_min_row, c)) {
                    cur_min_row = r;
                }
            }
            res(0, c) = static_cast<double>(cur_min_row); 
        }
        return res;
    }
}

//==============================
// Solvers
//==============================

LUResult Matrix::lu_decompose() const {
    if (rows_ != cols_)
        throw std::runtime_error("LU decomposition requires a square matrix\n");

    LUResult lu;
    lu.n        = rows_;
    lu.data     = data_;  
    lu.sign     = 1;
    lu.singular = false;

    for (size_t i = 0; i < rows_; i++)
        lu.perm.push_back(i);

    constexpr double EPSILON = 1e-9;

    // lambda to index into lu.data as a 2D matrix
    auto LU = [&](size_t r, size_t c) -> double& {
        return lu.data[r * lu.n + c];
    };

    for (size_t k = 0; k < lu.n; k++) {
        // find pivot with largest abs value in col k at or below row k
        size_t cur_max_idx = k;
        for (size_t r = k + 1; r < lu.n; r++)
            if (std::abs(LU(r, k)) > std::abs(LU(cur_max_idx, k)))
                cur_max_idx = r;

        // swap rows in lu.data and perm if better pivot found
        if (cur_max_idx != k) {
            for (size_t c = 0; c < lu.n; c++)
                std::swap(LU(k, c), LU(cur_max_idx, c));
            std::swap(lu.perm[k], lu.perm[cur_max_idx]);
            lu.sign *= -1;
        }

        // after best swap, if pivot still ~0 — singular
        if (std::abs(LU(k, k)) < EPSILON) {
            lu.singular = true;
            return lu;
        }
    
        // elimination — zero out col k below diagonal
        for (size_t i = k + 1; i < lu.n; i++) {
            double factor = LU(i, k) / LU(k, k);
            LU(i, k) = factor;                      // store L factor
            for (size_t j = k + 1; j < lu.n; j++)
                LU(i, j) -= factor * LU(k, j);      // update upper triangle
        }
    }
    return lu;
}

Matrix Matrix::inverse() const {
    if (rows_ != cols_)
        throw std::runtime_error("Matrix is not invertible due to dimension mismatch\n");

    Matrix working = *this;
    Matrix augmented = Matrix::identity(rows_);

    // Forward elimination with partial pivoting
    for (size_t k = 0; k < cols_; k++) {
        // find the largest abs value in col r
        size_t cur_max_row = k;
        for (size_t r = k + 1; r < rows_; r++) {
            if (std::abs(working(r, k)) > std::abs(working(cur_max_row, k)))
                cur_max_row = r;
        }

        // swap both the working and augmented matrices if a larger absolute value was found
        if (cur_max_row != k) {
            for (size_t c = 0; c < working.cols() ; c++) {
                std::swap(working(k, c), working(cur_max_row, c));
                std::swap(augmented(k, c), augmented(cur_max_row, c));
            }
        }

        double pv = working(k, k);
        // guard against zero division
        if (std::abs(pv) < 1e-9)
            throw std::runtime_error("Matrix is singular\n");

        // scale the pivot row to make diagonal exactly 1
        for (size_t c = k; c < cols_; c++) {
            working(k, c) /= pv;
        }
        for (size_t c = 0; c < cols_; c++) {
            augmented(k, c) /= pv;
        }

        // eliminate the rows below
        for (size_t r = k + 1; r < rows_; r++) {
            double factor = working(r, k);

            // update from the pivot col to the end across the row
            for (size_t c = k; c < cols_; c++) {
                working(r, c) -= factor * working(k, c);
            }
            // update the entire row for augmented
            for (size_t c = 0; c < cols_; c++) {
                augmented(r, c) -= factor * augmented(k, c);
            }
        }
    }
    // Backward elimination
    for (int k = static_cast<int>(cols_) - 1; k >= 0; k--) {

        // clear the rows above the pivot row
        for (size_t r = 0; r < static_cast<size_t>(k); r++) {
            // factor is always target row because pivot is 1
            double factor = working(r, k);

            // clear each column of that row for augmented
            for (size_t c = 0; c < cols_; c++) {
                augmented(r, c) -= factor * augmented(k, c);
            }
            // eliminate target cell
            working(r, k) = 0.0;
        }
    }
    return augmented;
}

double Matrix::determinant() const {
    auto lu = Matrix::lu_decompose();
    if (lu.singular)
        return 0.0;

    double det = static_cast<double>(lu.sign);
    for (size_t i = 0; i < lu.n; i++) {
        det *= lu.data[i * lu.n + i];
    }
    return det;
}

// PA = LU method
Matrix Matrix::solve(const Matrix& b) const {
    if (rows_ != cols_)
        throw std::runtime_error("Solve requires a square matrix\n");
    if (b.rows() != rows_ || b.cols() != 1)
        throw std::runtime_error("Matrix b must be a column vector of matching size\n");

    auto lu = lu_decompose();

    if (lu.singular) 
        throw std::runtime_error("Matrix is singular - unable to solve the system\n");

    std::vector<double> pb(b.data_.size());

    // pb = permuation vector from lu applied on b
    for (size_t i = 0; i < b.data_.size(); i++) {
        pb[i] = b.data_[lu.perm[i]];
    }

    std::vector<double> y(lu.n);
    // forward substitution (Ly = pb, where y = Ux)
    for (size_t i = 0; i < lu.n; i++) {
        y[i] = pb[i];
        // [1 0 0]   [x0]
        // [1 2 0] * [x1]
        // [1 2 3]   [x2]
        for (size_t j = 0; j < i; j++) {
            y[i] -= lu.data[i * lu.n + j] * y[j];
        }
    }

    // backward substitution (Ux = y)
    // subtract from i + 1 and divide by i, i
    std::vector<double> x(lu.n);
    for (int i = static_cast<int>(lu.n) - 1; i >= 0; i--) {
        x[i] = y[i];
        // [8 7 9]   [x0]   y0
        // [0 1 2] * [x1] = y1
        // [0 0 1]   [x2]   y2
        for (size_t j = static_cast<size_t>(i) + 1; j < lu.n; j++) {
            x[i] -= lu.data[i * lu.n + j] * x[j];
        }
        x[i] /= lu.data[i * lu.n + i];
    }

    Matrix res(b.rows(), 1);
    for (size_t i = 0; i < x.size(); i++) {
        res.data_[i] = x[i];
    }
    return res;
}

Matrix Matrix::random(size_t rows, size_t cols, double low, double high) {
    if (low > high)
        throw std::runtime_error("Minimum input is less than the maximum input\n");
    // random seed
    std::random_device rd;
    // engine
    std::mt19937 gen(rd());
    // distribution range
    std::uniform_real_distribution distr(low, high);

    Matrix random(rows, cols);
    for (size_t i = 0; i < random.data_.size(); i++) {
        random.data_[i] = distr(gen);
    }
    return random;
}

Matrix Matrix::row(size_t r) const {
    if (r >= rows_ || r < 0) 
        throw std::runtime_error("Invalid row dimension\n");

    Matrix res(1, cols_);
    for (size_t i = 0; i < cols_; i++) {
        res(0, i) = data_[r * cols_ + i];
    }
    return res;
}

Matrix Matrix::col(size_t c) const {
    if (c >= cols_ || c < 0)
        throw std::runtime_error("Invalid column dimension\n");

    Matrix res(rows_, 1);
    for (size_t i = 0; i < rows_; i++) {
        res(i, 0) = data_[i * cols_ + c];
    }
    return res;
}

Matrix Matrix::outer_product(const Matrix& col, const Matrix& row) {
    if (col.cols() != 1)
        throw std::runtime_error("Invalid column vector dimension\n");
    if (row.rows() != 1)
        throw std::runtime_error("Invalid row vector dimension\n");
        
    // Work only on 2 vectors
    // This becomes uv^T ( u multiplied by v transposed ) or column vector * row vector
    Matrix res(col.rows(), row.cols());
    for (size_t r = 0; r < col.rows(); r++) {
        for (size_t c = 0; c < row.cols(); c++) {
            res(r, c) = col(r, 0) * row(0, c);
        }
    }    
    return res;
}

double Matrix::trace() const {
    if (rows_ != cols_)
        throw std::runtime_error("Unable to compute the trace for non-square matrix\n");

    double trace = 0.0;
    for (size_t i = 0; i < data_.size(); i++) {
        trace += data_[i * cols_ + i];
    }
    return trace;
}

Matrix Matrix::broadcast_add(const Matrix& vec, int axis) const {
    // Row-wise
    if (axis == 0) {
        if (vec.rows() != 1 or vec.cols() != cols_)
            throw std::runtime_error("Invalid row vector dimension\n");

        Matrix res = *this;
        for (size_t r = 0; r < rows_; r++) {
            for (size_t c = 0; c < cols_; c++) {
                res(r, c) += vec(0, c);
            }
        }
        return res;
    }
    // Column-wise
    if (axis == 1) {
        if (vec.cols() != 1 or vec.rows() != rows())
            throw std::runtime_error("Invalid column vector dimension\n");

        Matrix res = *this;
        for (size_t r = 0; r < rows_; r++) {
            for (size_t c = 0; c < cols_; c++) {
                res(r, c) += vec(r, 0);
            }
        }
        return res;
    }
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