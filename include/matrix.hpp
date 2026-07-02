/**
 * include/matrix.hpp
 * author: Bao Le
 */

#pragma once

#include <vector>
#include <cstddef>   
#include <stdexcept> 
#include <iostream>
#include <optional>
#include <tuple>

class Matrix {
    public:
        // default constructor, all zeroes
        Matrix(size_t rows, size_t cols);
        // constructor with specific inputs
        Matrix(size_t rows, size_t cols, std::vector<double> ip);

        // Matrix shape (rows, cols)
        std::tuple<size_t, size_t> shape() const;
        
        // Element access
        double operator()(size_t r, size_t c) const;    // reading
        double& operator()(size_t r, size_t c); // writing

        // Dimensions
        size_t rows() const { return rows_; }
        size_t cols() const { return cols_; }

        // Matrix multiply - the core operation
        Matrix operator*(const Matrix& other) const;
        Matrix operator*(double factor) const;

        // Addition
        Matrix operator+(const Matrix& other) const;
        Matrix operator+=(const Matrix& other);

        // Subtraction
        Matrix operator-(const Matrix& other) const;
        Matrix operator-=(const Matrix& other);

        // Print
        void print() const;

    private:
        size_t rows_, cols_;
        std::vector<double> data_;  // row-major storage
};