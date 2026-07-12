/**
 * include/matrix.hpp
 * author: Bao Le
 */

#pragma once
#include <vector>
#include <cstddef>
#include <functional>
#include <ostream>
#include <tuple>
#include <cmath>
#include <string>
#include <random>

struct LUResult {
    std::vector<double> data;
    size_t n = 0;
    std::vector<size_t> perm;
    int  sign = 1;
    bool singular = false;
};

class Matrix {
    private:
        size_t rows_, cols_;
        std::vector<double> data_;  // row-major storage

        inline double& at(size_t r, size_t c) noexcept { return data_[r * cols_ + c]; }
        inline double  at(size_t r, size_t c) const noexcept { return data_[r * cols_ + c]; }

    public:
        //==============================
        // Constructors
        //==============================
        Matrix();
        Matrix(size_t rows, size_t cols);
        Matrix(size_t rows, size_t cols, std::vector<double> ip);

        //==============================
        // Shape
        //==============================
        [[nodiscard]] std::tuple<size_t, size_t> shape() const noexcept;
        [[nodiscard]] size_t rows() const noexcept { return rows_; }
        [[nodiscard]] size_t cols() const noexcept { return cols_; }
        [[nodiscard]] Matrix row(size_t r) const;
        [[nodiscard]] Matrix col(size_t c) const;

        //==============================
        // Element Access
        //==============================
        double  operator()(size_t r, size_t c) const;
        double& operator()(size_t r, size_t c);

        //==============================
        // Arithmetic
        //==============================
        [[nodiscard]] Matrix  operator*(const Matrix& other) const;
        [[nodiscard]] Matrix  operator*(double factor) const;
                    Matrix& operator*=(const Matrix& other);
                    Matrix& operator*=(double factor);
        [[nodiscard]] Matrix  elementwise_multiply(const Matrix& other) const;

        [[nodiscard]] Matrix  operator+(const Matrix& other) const;
                    Matrix& operator+=(const Matrix& other);
        [[nodiscard]] Matrix  operator+(double scalar) const;
                    Matrix& operator+=(double scalar);

        [[nodiscard]] Matrix  operator-(const Matrix& other) const;
                    Matrix& operator-=(const Matrix& other);
        [[nodiscard]] Matrix  operator-(double scalar) const;
                    Matrix& operator-=(double scalar);

        [[nodiscard]] Matrix  operator/(double scalar) const;
                    Matrix& operator/=(double scalar);

        [[nodiscard]] double dot(const Matrix& other) const;
        [[nodiscard]] static Matrix outer_product(const Matrix& col, const Matrix& row);
        [[nodiscard]] double trace() const;

        //==============================
        // Comparison
        //==============================
        [[nodiscard]] bool operator==(const Matrix& other) const;
        [[nodiscard]] bool operator!=(const Matrix& other) const;

        //==============================
        // Norms
        //==============================
        [[nodiscard]] double l1_elementwise_norm() const;  // absolute sum of all elements
        [[nodiscard]] double l1_induced_norm() const;      // max absolute column sum
        [[nodiscard]] double l2_norm() const;              // frobenius / euclidean norm
        [[nodiscard]] double inf_norm() const;             // max absolute row sum

        //==============================
        // Structural
        //==============================
        [[nodiscard]] Matrix transpose() const;
        [[nodiscard]] Matrix slice(size_t r0, size_t r1, size_t c0, size_t c1) const;
        [[nodiscard]] Matrix reshape(size_t rows, size_t cols) const;
        [[nodiscard]] Matrix flatten() const;

        //==============================
        // Reductions
        //==============================
        [[nodiscard]] double sum() const;
        [[nodiscard]] Matrix sum(int axis) const;
        [[nodiscard]] double mean() const;
        [[nodiscard]] Matrix mean(int axis) const;
        [[nodiscard]] double max() const;
        [[nodiscard]] Matrix max(int axis) const;
        [[nodiscard]] double min() const;
        [[nodiscard]] Matrix min(int axis) const;

        //==============================
        // Arg Reductions
        //==============================
        [[nodiscard]] size_t argmax() const;
        [[nodiscard]] size_t argmin() const;
        [[nodiscard]] Matrix argmax(int axis) const;
        [[nodiscard]] Matrix argmin(int axis) const;

        //==============================
        // Application
        //==============================
        [[nodiscard]] Matrix  apply(std::function<double(double)> func) const;
                    Matrix& apply_(std::function<double(double)> func);

        //==============================
        // Static Factories
        //==============================
        [[nodiscard]] static Matrix zeros(size_t rows, size_t cols);
        [[nodiscard]] static Matrix ones(size_t rows, size_t cols);
        [[nodiscard]] static Matrix identity(size_t n);
        [[nodiscard]] static Matrix hstack(const Matrix& a, const Matrix& b);
        [[nodiscard]] static Matrix vstack(const Matrix& a, const Matrix& b);
        [[nodiscard]] static Matrix load(const std::string& filename);
        [[nodiscard]] static Matrix random(size_t rows, size_t cols, double low = 0.0, double high = 1.0);

        //==============================
        // Utilities
        //==============================
                    void fill(double value);
        [[nodiscard]] Matrix clip(double min_val, double max_val) const;
                    void save(const std::string& filename) const;

        //==============================
        // Linear Algebra
        //==============================
        LUResult lu_decompose() const;
        [[nodiscard]] double determinant() const;
        [[nodiscard]] Matrix inverse() const;
        [[nodiscard]] Matrix solve(const Matrix& b) const;

        //==============================
        // Output
        //==============================
        friend std::ostream& operator<<(std::ostream& os, const Matrix& m);
};