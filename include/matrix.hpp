/**
 * include/matrix.hpp
 * author: Bao Le
 */

#pragma once

#include <fstream>
#include <vector>
#include <cstddef>   
#include <stdexcept> 
#include <iostream>
#include <optional>
#include <tuple>

class Matrix {
    private:
        size_t rows_, cols_;
        std::vector<double> data_;  // row-major storage

        inline double& at(size_t r, size_t c) noexcept { return data_[r * cols_ + c]; }
        inline double  at(size_t r, size_t c) const noexcept { return data_[r * cols_ + c]; }
    public:
        Matrix();
        // default constructor, all zeroes
        Matrix(size_t rows, size_t cols);
        // constructor with specific inputs
        Matrix(size_t rows, size_t cols, std::vector<double> ip);

        // Matrix shape (rows, cols)
        [[nodiscard]] std::tuple<size_t, size_t> shape() const noexcept;
        
        // Element access
        double operator()(size_t r, size_t c) const;    // reading
        double& operator()(size_t r, size_t c); // writing

        // Dimensions
        [[nodiscard]] size_t rows() const noexcept { return rows_; }
        [[nodiscard]] size_t cols() const noexcept { return cols_; }

        // Multiplication
        [[nodiscard]] Matrix operator*(const Matrix& other) const;
        [[nodiscard]] Matrix operator*(double factor) const;
                      Matrix& operator*=(const Matrix& other);
                      Matrix& operator*=(double factor);
        [[nodiscard]] Matrix elementwise_multiply(const Matrix& other) const;

        // Addition
        [[nodiscard]] Matrix operator+(const Matrix& other) const;
                      Matrix& operator+=(const Matrix& other);
        [[nodiscard]] Matrix operator+(double scalar) const;
                      Matrix& operator+=(double scalar);

        // Subtraction
        [[nodiscard]] Matrix operator-(const Matrix& other) const;
                      Matrix& operator-=(const Matrix& other);
        [[nodiscard]] Matrix operator-(double scalar) const;
                      Matrix& operator-=(double scalar);

        // Division
        [[nodiscard]] Matrix operator/(double scalar) const;
                      Matrix& operator/= (double scalar);

        // Dot product
        [[nodiscard]] double dot(const Matrix& other) const;

        // Norms
        [[nodiscard]] double l1_elementwise_norm() const;   // manhattan or taxicab norm
        [[nodiscard]] double l1_induced_norm() const;   // max absolute sum of columns
        [[nodiscard]] double l2_norm() const;   // frobenius norm for matrix or euclidean norm for vector
        [[nodiscard]] double inf_norm() const; // max or infinity norm

        // Comparison
        [[nodiscard]] bool operator==(const Matrix& other) const;
        [[nodiscard]] bool operator!=(const Matrix& other) const;

        // Structural
        [[nodiscard]] Matrix transpose() const;
        [[nodiscard]] Matrix slice(size_t r0, size_t r1, size_t c0, size_t c1) const;

        // Reductions
        [[nodiscard]] double sum() const;
        [[nodiscard]] Matrix sum(int axis) const;
        [[nodiscard]] Matrix mean(int axis) const;
        [[nodiscard]] double mean() const;
        [[nodiscard]] double max() const;
        [[nodiscard]] Matrix max(int axis) const;
        [[nodiscard]] double min() const;
        [[nodiscard]] Matrix min(int axis) const;

        // Custom application
        [[nodiscard]] Matrix apply(std::function<double(double)> func) const; 
                      Matrix& apply_(std::function<double(double)> func); 
        
        // Matrix utils
        [[nodiscard]] static Matrix zeros(size_t rows, size_t cols);
        [[nodiscard]] static Matrix ones(size_t rows, size_t cols);
        [[nodiscard]] static Matrix identity(size_t n);

                      void fill(double value); 
                      Matrix clip(double min, double max);
        [[nodiscard]] Matrix reshape(double row, double col) const;
        [[nodiscard]] Matrix flatten() const;

        [[nodiscard]] static Matrix hstack(const Matrix& a, const Matrix& b); // side by side
        [[nodiscard]] static Matrix vstack(const Matrix& a, const Matrix& b); // on top

        // To implement
        // Linear algebra
        [[nodiscard]] Matrix inverse() const;
        [[nodiscard]] double determinant() const;
        [[nodiscard]] Matrix solve(const Matrix& b) const;      

        [[nodiscard]] size_t argmax() const;          // index in flat data_
        [[nodiscard]] size_t argmin() const;
        [[nodiscard]] Matrix argmax(int axis) const;  // per row or col
        [[nodiscard]] Matrix argmin(int axis) const;
    
        void save(const std::string& filename) const;   // write to CSV
        [[nodiscard]] static Matrix load(const std::string& filename); // read from CSV
        
        friend std::ostream& operator<<(std::ostream& os, const Matrix& m);
};